#include "core/Interpreter.h"

#include <fstream>

#include "core/Pipeline.h"
#include "errors/InterpreterExceptions.h"
#include "parsing/Lexer.h"
#include "parsing/Parser.h"
#include "streams/ConsoleOutputStream.h"

namespace cli {

    namespace {
        constexpr size_t kMaxCommandLineLength = 512;
    }

    Interpreter::Interpreter(std::istream& in, std::ostream& out, std::ostream& err)
            : in_(in), out_(out), err_(err),
              factory_(
                      [this](const std::string& newPrompt) { this->setPrompt(newPrompt); },
                      [this](const std::string& filename,
                             std::shared_ptr<OutputStream> defaultOut,
                             std::shared_ptr<OutputStream> defaultErr) {
                          this->runBatchFile(filename, std::move(defaultOut), std::move(defaultErr));
                      }) {
        consoleInput_ = std::make_shared<ConsoleInputStream>(0);
        consoleOutput_ = std::make_shared<ConsoleOutputStream>(out_);
        consoleError_ = std::make_shared<ConsoleOutputStream>(err_);
    }

    bool Interpreter::readLine(std::istream& in, std::string& out) {
        out.clear();
        if (!in.good()) return false;

        char c;
        bool readAnything = false;
        size_t count = 0;
        while (in.get(c)) {
            readAnything = true;
            if (c == '\n') break;
            if (count < kMaxCommandLineLength) {
                out.push_back(c);
                ++count;
            }
        }
        return readAnything;
    }

    bool Interpreter::readLineFromConsole(std::string& out) {
        out.clear();

        char c;
        bool readAnything = false;
        size_t count = 0;
        while (consoleInput_->getChar(c)) {
            readAnything = true;
            if (c == '\n') break;
            if (count < kMaxCommandLineLength) {
                out.push_back(c);
                ++count;
            }
        }
        return readAnything;
    }

    void Interpreter::executeLine(const std::string& line,
                                  std::shared_ptr<OutputStream> defaultOutput,
                                  std::shared_ptr<OutputStream> defaultError,
                                  std::shared_ptr<InputStream> defaultConsoleInput) {
        try {
            Lexer lexer;
            std::vector<Token> tokens = lexer.tokenize(line);
            if (tokens.empty()) return;

            Parser parser(factory_);
            std::vector<ParsedCommand> stages = parser.parse(tokens);

            Pipeline pipeline(std::move(stages), defaultOutput, defaultError, defaultConsoleInput);
            pipeline.run();
        } catch (const LexicalError& e) {
            defaultError->putString(std::string(e.what()) + "\n");
            defaultError->putString(line + "\n");
            std::string caret(line.size(), ' ');
            for (size_t pos : e.getPositions()) {
                if (pos < caret.size()) caret[pos] = '^';
            }
            defaultError->putString(caret + "\n");
        } catch (const InterpreterException& e) {
            defaultError->putString(std::string(e.what()) + "\n");
        }

        consoleInput_->resetEof();
        consoleOutput_->ensureNewline();
    }

    void Interpreter::run() {
        std::string line;
        while (true) {
            out_ << prompt_;
            out_.flush();
            if (!readLineFromConsole(line)) break;
            executeLine(line, consoleOutput_, consoleError_, consoleInput_);
        }
        out_ << std::endl;
    }

    void Interpreter::runBatchFile(const std::string& filename,
                                   std::shared_ptr<OutputStream> defaultOutput,
                                   std::shared_ptr<OutputStream> defaultError) {
        std::ifstream file(filename, std::ios::in);
        if (!file.is_open()) {
            throw FileSystemError("batch: cannot open file: " + filename);
        }

        std::string line;
        while (readLine(file, line)) {
            executeLine(line, defaultOutput, defaultError, consoleInput_);
        }
    }

} // namespace cli
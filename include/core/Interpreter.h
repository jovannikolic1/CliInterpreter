#ifndef CLI_INTERPRETER_H
#define CLI_INTERPRETER_H

#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "commands/CommandFactory.h"
#include "streams/ConsoleInputStream.h"
#include "streams/ConsoleOutputStream.h"
#include "streams/InputStream.h"
#include "streams/OutputStream.h"

namespace cli {


    class Interpreter {
    public:
        Interpreter(std::istream& in, std::ostream& out, std::ostream& err);

        void run();

        void runBatchFile(const std::string& filename,std::shared_ptr<OutputStream> defaultOutput,std::shared_ptr<OutputStream> defaultError);

        void setPrompt(const std::string& newPrompt) { prompt_ = newPrompt; }

    private:
        void executeLine(const std::string& line,std::shared_ptr<OutputStream> defaultOutput,std::shared_ptr<OutputStream> defaultError,std::shared_ptr<InputStream> defaultConsoleInput);

        static bool readLine(std::istream& in, std::string& out);

        bool readLineFromConsole(std::string& out);

        std::istream& in_;
        std::ostream& out_;
        std::ostream& err_;
        std::string prompt_ = "$";
        CommandFactory factory_;

        std::shared_ptr<ConsoleInputStream> consoleInput_;
        std::shared_ptr<ConsoleOutputStream> consoleOutput_;
        std::shared_ptr<OutputStream> consoleError_;
    };

} // namespace cli

#endif // CLI_INTERPRETER_H
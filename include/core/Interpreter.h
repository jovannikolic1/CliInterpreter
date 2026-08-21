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

// Drives the whole read-eval-print loop described by the specification:
// prints the prompt, reads one command line (respecting the 512-character
// limit), lexes/parses/executes it as a pipeline, and reports any error
// that occurs along the way -- then starts over.
//
// Also used (via runBatchFile()) by BatchCommand to interpret every line
// of a batch file exactly the same way, just with a different default
// input/output/error target.
//
// Known simplification (documented, see README "Assumptions"): the
// specification asks that, inside a batch file, a command that is missing
// a *mandatory plain argument* (e.g. "touch" with no filename) and is the
// first command of its pipeline should interactively read that argument
// from the real console instead of failing. This implementation reports a
// syntax error in that case instead, exactly as it would at the top level.
// Commands whose *input character stream* falls back to the console
// (e.g. "wc -w" with no argument/redirect) already transparently read from
// the real console even inside a batch file, since runBatchFile() reuses
// the interpreter's own console input stream as the pipeline's default.
    class Interpreter {
    public:
        Interpreter(std::istream& in, std::ostream& out, std::ostream& err);

        // Runs the interactive read-eval-print loop until the input stream
        // reaches end-of-file.
        void run();

        // Executes every line found in 'filename' as its own command line,
        // using defaultOutput/defaultError as the default output/error target
        // for commands that do not redirect explicitly. Used by BatchCommand.
        void runBatchFile(const std::string& filename,
                          std::shared_ptr<OutputStream> defaultOutput,
                          std::shared_ptr<OutputStream> defaultError);

        void setPrompt(const std::string& newPrompt) { prompt_ = newPrompt; }

    private:
        // Parses and executes a single, already-read command line. Any
        // exception raised while lexing/parsing/executing is caught here and
        // turned into a message on 'errorTarget'.
        void executeLine(const std::string& line,
                         std::shared_ptr<OutputStream> defaultOutput,
                         std::shared_ptr<OutputStream> defaultError,
                         std::shared_ptr<InputStream> defaultConsoleInput);

        // Reads one line of at most 512 characters from 'in' (a text file,
        // e.g. inside a batch script), discarding any extra characters up to
        // the next '\n' as required by the specification. Returns false at
        // end-of-file with no characters read.
        static bool readLine(std::istream& in, std::string& out);

        // Same idea, but reads directly from the real console via
        // consoleInput_ (see ConsoleInputStream for why this is not simply
        // std::cin). Used by the interactive run() loop.
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
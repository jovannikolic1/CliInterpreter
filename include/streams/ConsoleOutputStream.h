#ifndef CLI_CONSOLE_OUTPUT_STREAM_H
#define CLI_CONSOLE_OUTPUT_STREAM_H

#include <ostream>

#include "streams/OutputStream.h"

namespace cli {

// Output stream that writes directly to the console (an std::ostream,
// normally std::cout or std::cerr).
    class ConsoleOutputStream : public OutputStream {
    public:
        explicit ConsoleOutputStream(std::ostream& out) : out_(out) {}

        void putChar(char c) override;

        // True if the last character written through this stream was '\n'
        // (or if nothing has been written yet).
        bool endsWithNewline() const { return lastWasNewline_; }

        // If the last character written was not '\n', writes one now. Used
        // by the Interpreter to guarantee that the prompt (and, in a batch
        // file, the next command's output) always starts "at the beginning
        // of a new line", as required by the specification, even though
        // individual commands (echo, wc, time, date, ...) never add a
        // trailing newline of their own.
        void ensureNewline();

    private:
        std::ostream& out_;
        bool lastWasNewline_ = true;
    };

} // namespace cli

#endif // CLI_CONSOLE_OUTPUT_STREAM_H
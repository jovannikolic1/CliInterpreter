#ifndef CLI_CONSOLE_OUTPUT_STREAM_H
#define CLI_CONSOLE_OUTPUT_STREAM_H

#include <ostream>

#include "streams/OutputStream.h"

namespace cli {

    class ConsoleOutputStream : public OutputStream {
    public:
        explicit ConsoleOutputStream(std::ostream& out) : out_(out) {}

        void putChar(char c) override;

        bool endsWithNewline() const { return lastWasNewline_; }

        void ensureNewline();

    private:
        std::ostream& out_;
        bool lastWasNewline_ = true;
    };

} // namespace cli

#endif // CLI_CONSOLE_OUTPUT_STREAM_H
#ifndef CLI_CONSOLE_INPUT_STREAM_H
#define CLI_CONSOLE_INPUT_STREAM_H

#include "streams/InputStream.h"

namespace cli {

    class ConsoleInputStream : public InputStream {
    public:
        explicit ConsoleInputStream(int fd = 0) : fd_(fd) {}

        bool getChar(char& out) override;
        bool eof() const override { return atEof_; }

        void resetEof() { atEof_ = false; }

    private:
        int fd_;
        bool atEof_ = false;
    };

} // namespace cli

#endif // CLI_CONSOLE_INPUT_STREAM_H
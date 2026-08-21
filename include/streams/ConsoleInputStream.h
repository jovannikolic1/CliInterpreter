#ifndef CLI_CONSOLE_INPUT_STREAM_H
#define CLI_CONSOLE_INPUT_STREAM_H

#include "streams/InputStream.h"

namespace cli {

// Input stream that reads directly from the console using a low-level
// POSIX read() call on the given file descriptor (STDIN_FILENO by
// default), one byte at a time, until the operating-system EOF sequence
// (Ctrl+D / Ctrl+Z) is entered.
//
// A raw read() is used on purpose, instead of std::cin/std::istream: some
// C++ standard library implementations (notably libc++ on macOS) can
// leave an interactive std::cin in a state where, after one EOF has been
// signalled and the stream cleared with clear(), further reads
// incorrectly report EOF again immediately instead of blocking for new
// terminal input. A bare POSIX read() on the file descriptor carries no
// such persistent state: every call is independent and simply blocks
// until the terminal actually has something to deliver, which matches
// the real behaviour of Ctrl+D in canonical terminal mode (it only ends
// the *current* pending read, not the file descriptor itself).
    class ConsoleInputStream : public InputStream {
    public:
        explicit ConsoleInputStream(int fd = 0) : fd_(fd) {}

        bool getChar(char& out) override;
        bool eof() const override { return atEof_; }

        // Called after a command that used this stream is done: allows the
        // console to be read from again by a later command / prompt, even
        // though the previous read ended in an EOF signal.
        void resetEof() { atEof_ = false; }

    private:
        int fd_;
        bool atEof_ = false;
    };

} // namespace cli

#endif // CLI_CONSOLE_INPUT_STREAM_H
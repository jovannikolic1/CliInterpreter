#include "streams/ConsoleInputStream.h"

#include <unistd.h>

namespace cli {

    bool ConsoleInputStream::getChar(char& out) {
        if (atEof_) return false;

        char c;
        ssize_t n = ::read(fd_, &c, 1);
        if (n <= 0) {
            // n == 0: end of input (Ctrl+D / Ctrl+Z, or a real closed stream).
            // n <  0: a read error; treated the same way, as there is nothing
            // sensible left to read.
            atEof_ = true;
            return false;
        }
        out = c;
        return true;
    }

} // namespace cli
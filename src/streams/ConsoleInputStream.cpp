#include "streams/ConsoleInputStream.h"

#include <unistd.h>

namespace cli {

    bool ConsoleInputStream::getChar(char& out) {
        if (atEof_) return false;

        char c;
        ssize_t n = ::read(fd_, &c, 1);
        if (n <= 0) {
            atEof_ = true;
            return false;
        }
        out = c;
        return true;
    }

} // namespace cli
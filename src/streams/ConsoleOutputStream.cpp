#include "streams/ConsoleOutputStream.h"

namespace cli {

    void ConsoleOutputStream::putChar(char c) {
        out_.put(c);
        out_.flush();
        lastWasNewline_ = (c == '\n');
    }

    void ConsoleOutputStream::ensureNewline() {
        if (!lastWasNewline_) {
            putChar('\n');
        }
    }

} // namespace cli
#include "streams/InputStream.h"

namespace cli {

std::string InputStream::readAll() {
    std::string result;
    char c;
    while (getChar(c)) {
        result.push_back(c);
    }
    return result;
}

} // namespace cli

#include "streams/StringInputStream.h"

namespace cli {

bool StringInputStream::getChar(char& out) {
    if (position_ >= content_.size()) return false;
    out = content_[position_++];
    return true;
}

bool StringInputStream::eof() const {
    return position_ >= content_.size();
}

} // namespace cli

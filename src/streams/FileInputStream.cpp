#include "streams/FileInputStream.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

FileInputStream::FileInputStream(const std::string& filename)
    : filename_(filename) {
    file_.open(filename_, std::ios::in);
    if (!file_.is_open()) {
        throw FileSystemError("cannot open file for reading: " + filename_);
    }
}

bool FileInputStream::getChar(char& out) {
    char c;
    if (file_.get(c)) {
        out = c;
        return true;
    }
    return false;
}

bool FileInputStream::eof() const {
    return file_.eof();
}

} // namespace cli

#include "streams/FileOutputStream.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

FileOutputStream::FileOutputStream(const std::string& filename, bool append)
    : filename_(filename) {
    auto mode = std::ios::out | (append ? std::ios::app : std::ios::trunc);
    file_.open(filename_, mode);
    if (!file_.is_open()) {
        throw FileSystemError("cannot open file for writing: " + filename_);
    }
}

void FileOutputStream::putChar(char c) {
    file_.put(c);
}

} // namespace cli

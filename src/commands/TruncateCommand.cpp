#include "commands/TruncateCommand.h"

#include <fstream>
#include <sys/stat.h>

#include "errors/InterpreterExceptions.h"

namespace cli {

void TruncateCommand::performAction(const std::string& filename) {
    struct stat buffer{};
    if (stat(filename.c_str(), &buffer) != 0) {
        throw FileSystemError("truncate: file does not exist: " + filename);
    }
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw FileSystemError("truncate: cannot open file: " + filename);
    }
}

} // namespace cli

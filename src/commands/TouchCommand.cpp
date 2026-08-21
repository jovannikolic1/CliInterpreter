#include "commands/TouchCommand.h"

#include <fstream>
#include <sys/stat.h>

#include "errors/InterpreterExceptions.h"

namespace cli {

void TouchCommand::performAction(const std::string& filename) {
    struct stat buffer{};
    if (stat(filename.c_str(), &buffer) == 0) {
        throw FileSystemError("touch: file already exists: " + filename);
    }
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        throw FileSystemError("touch: cannot create file: " + filename);
    }
}

} // namespace cli

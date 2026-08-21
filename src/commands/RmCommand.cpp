#include "commands/RmCommand.h"

#include <cstdio>

#include "errors/InterpreterExceptions.h"

namespace cli {

void RmCommand::performAction(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        throw FileSystemError("rm: cannot remove file: " + filename);
    }
}

} // namespace cli

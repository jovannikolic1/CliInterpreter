#include "commands/FileNameCommand.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

void FileNameCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.size() != 1 || !tokens[0].isWord()) {
        throw SyntaxError(name() + ": expected exactly one filename argument");
    }
    filename_ = tokens[0].getText();
}

void FileNameCommand::execute() {
    performAction(filename_);
}

} // namespace cli

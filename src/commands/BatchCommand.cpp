#include "commands/BatchCommand.h"

#include "errors/InterpreterExceptions.h"
namespace cli {

void BatchCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.size() != 1 || !tokens[0].isWord()) {
        throw SyntaxError("batch: expected exactly one filename argument");
    }
    filename_ = tokens[0].getText();
}

void BatchCommand::execute() {
    if (runner_) {
        runner_(filename_, output_, error_);
    }
}

} // namespace cli

#include "commands/EchoCommand.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

void EchoCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.empty()) {
        return; // no argument
    }
    if (tokens.size() > 1) {
        throw SyntaxError("echo: too many arguments");
    }
    const Token& t = tokens[0];
    if (t.isQuoted()) {
        setOwnArgument(t.getText(), true);
    } else if (t.isWord()) {
        setOwnArgument(t.getText(), false);
    } else {
        throw SyntaxError("echo: invalid argument");
    }
}

    void EchoCommand::execute() {
        output_->putString(input_->readAll());
    }

} // namespace cli

#include "commands/PromptCommand.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

void PromptCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.size() != 1 || !tokens[0].isQuoted()) {
        throw SyntaxError("prompt: expected a single quoted argument");
    }
    newPrompt_ = tokens[0].getText();
}

void PromptCommand::execute() {
    if (setPrompt_) setPrompt_(newPrompt_);
}

} // namespace cli

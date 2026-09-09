#ifndef CLI_PROMPT_COMMAND_H
#define CLI_PROMPT_COMMAND_H

#include <functional>

#include "commands/Command.h"

namespace cli {

class PromptCommand : public Command {
public:
    using PromptSetter = std::function<void(const std::string&)>;

    explicit PromptCommand(PromptSetter setter) : setPrompt_(std::move(setter)) {}

    void parseArguments(const std::vector<Token>& tokens) override;
    void execute() override;
    std::string name() const override { return "prompt"; }

private:
    PromptSetter setPrompt_;
    std::string newPrompt_;
};

} // namespace cli

#endif // CLI_PROMPT_COMMAND_H

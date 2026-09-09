#ifndef CLI_COMMAND_FACTORY_H
#define CLI_COMMAND_FACTORY_H

#include <memory>
#include <string>

#include "commands/BatchCommand.h"
#include "commands/Command.h"
#include "commands/PromptCommand.h"

namespace cli {

class CommandFactory {
public:
    CommandFactory(PromptCommand::PromptSetter promptSetter,
                   BatchCommand::Runner batchRunner)
        : promptSetter_(std::move(promptSetter)),
          batchRunner_(std::move(batchRunner)) {}

    std::unique_ptr<Command> create(const std::string& commandName) const;

private:
    PromptCommand::PromptSetter promptSetter_;
    BatchCommand::Runner batchRunner_;
};

} // namespace cli

#endif // CLI_COMMAND_FACTORY_H

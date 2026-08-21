#ifndef CLI_COMMAND_FACTORY_H
#define CLI_COMMAND_FACTORY_H

#include <memory>
#include <string>

#include "commands/BatchCommand.h"
#include "commands/Command.h"
#include "commands/PromptCommand.h"

namespace cli {

// Creates a fresh Command instance for a given command name.
//
// New commands can be added later (the specification explicitly asks for
// an extensible system) simply by registering another branch here and
// adding the corresponding class under commands/ -- nothing else in the
// Lexer/Parser/Interpreter needs to change.
class CommandFactory {
public:
    CommandFactory(PromptCommand::PromptSetter promptSetter,
                   BatchCommand::Runner batchRunner)
        : promptSetter_(std::move(promptSetter)),
          batchRunner_(std::move(batchRunner)) {}

    // Throws cli::UnknownCommandError if 'commandName' is not recognized.
    std::unique_ptr<Command> create(const std::string& commandName) const;

private:
    PromptCommand::PromptSetter promptSetter_;
    BatchCommand::Runner batchRunner_;
};

} // namespace cli

#endif // CLI_COMMAND_FACTORY_H

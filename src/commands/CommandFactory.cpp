#include "commands/CommandFactory.h"

#include "commands/DateCommand.h"
#include "commands/EchoCommand.h"
#include "commands/HeadCommand.h"
#include "commands/RmCommand.h"
#include "commands/TimeCommand.h"
#include "commands/TouchCommand.h"
#include "commands/TrCommand.h"
#include "commands/TruncateCommand.h"
#include "commands/WcCommand.h"
#include "errors/InterpreterExceptions.h"

namespace cli {

std::unique_ptr<Command> CommandFactory::create(const std::string& commandName) const {
    if (commandName == "echo") return std::make_unique<EchoCommand>();
    if (commandName == "prompt") return std::make_unique<PromptCommand>(promptSetter_);
    if (commandName == "time") return std::make_unique<TimeCommand>();
    if (commandName == "date") return std::make_unique<DateCommand>();
    if (commandName == "touch") return std::make_unique<TouchCommand>();
    if (commandName == "truncate") return std::make_unique<TruncateCommand>();
    if (commandName == "rm") return std::make_unique<RmCommand>();
    if (commandName == "wc") return std::make_unique<WcCommand>();
    if (commandName == "tr") return std::make_unique<TrCommand>();
    if (commandName == "head") return std::make_unique<HeadCommand>();
    if (commandName == "batch") return std::make_unique<BatchCommand>(batchRunner_);

    throw UnknownCommandError(commandName);
}

} // namespace cli

#ifndef CLI_PARSED_COMMAND_H
#define CLI_PARSED_COMMAND_H

#include <memory>
#include <optional>
#include <string>

#include "commands/Command.h"

namespace cli {

struct ParsedCommand {
    std::unique_ptr<Command> command;
    std::optional<std::string> inputRedirectFile;   // set by '<'
    std::optional<std::string> outputRedirectFile;  // set by '>' or '>>'
    bool appendOutput = false;                      // true for '>>'
};

} // namespace cli

#endif // CLI_PARSED_COMMAND_H

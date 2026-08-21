#ifndef CLI_PARSED_COMMAND_H
#define CLI_PARSED_COMMAND_H

#include <memory>
#include <optional>
#include <string>

#include "commands/Command.h"

namespace cli {

// One stage of a (possibly one-stage) pipeline, as produced by the Parser:
// the already-argument-parsed Command object, plus whatever redirection
// was written after it on the command line. Wiring the actual InputStream/
// OutputStream objects (which also requires knowing whether this stage is
// first/last in the pipeline, and what the surrounding default streams
// are) is done afterwards, by the Pipeline class -- this struct only
// carries the raw syntactic information forward.
struct ParsedCommand {
    std::unique_ptr<Command> command;
    std::optional<std::string> inputRedirectFile;   // set by '<'
    std::optional<std::string> outputRedirectFile;  // set by '>' or '>>'
    bool appendOutput = false;                      // true for '>>'
};

} // namespace cli

#endif // CLI_PARSED_COMMAND_H

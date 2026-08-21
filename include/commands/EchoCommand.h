#ifndef CLI_ECHO_COMMAND_H
#define CLI_ECHO_COMMAND_H

#include "commands/Command.h"

namespace cli {

// echo [argument]
// Copies every character from its input stream to its output stream,
// unchanged.
class EchoCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesInputStream() const override { return true; }
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "echo"; }
};

} // namespace cli

#endif // CLI_ECHO_COMMAND_H

#ifndef CLI_TIME_COMMAND_H
#define CLI_TIME_COMMAND_H

#include "commands/Command.h"

namespace cli {

class TimeCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "time"; }
};

} // namespace cli

#endif // CLI_TIME_COMMAND_H

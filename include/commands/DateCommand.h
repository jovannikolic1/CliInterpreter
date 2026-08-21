#ifndef CLI_DATE_COMMAND_H
#define CLI_DATE_COMMAND_H

#include "commands/Command.h"

namespace cli {

// date
// Writes the current date to its output stream.
class DateCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "date"; }
};

} // namespace cli

#endif // CLI_DATE_COMMAND_H

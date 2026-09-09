#ifndef CLI_TR_COMMAND_H
#define CLI_TR_COMMAND_H

#include "commands/Command.h"

namespace cli {

class TrCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesInputStream() const override { return true; }
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "tr"; }

private:
    std::string what_;
    std::string with_;
    bool hasWith_ = false;
};

} // namespace cli

#endif // CLI_TR_COMMAND_H

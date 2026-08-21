#ifndef CLI_HEAD_COMMAND_H
#define CLI_HEAD_COMMAND_H

#include "commands/Command.h"

namespace cli {

// head -ncount [argument]
// Copies the first 'count' lines from the input stream to the output
// stream, ignoring the rest.
class HeadCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesInputStream() const override { return true; }
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "head"; }

private:
    int count_ = 0;
};

} // namespace cli

#endif // CLI_HEAD_COMMAND_H

#ifndef CLI_WC_COMMAND_H
#define CLI_WC_COMMAND_H

#include "commands/Command.h"

namespace cli {

class WcCommand : public Command {
public:
    enum class Mode { Words, Chars };

    void parseArguments(const std::vector<Token>& tokens) override;
    bool usesInputStream() const override { return true; }
    bool usesOutputStream() const override { return true; }
    void execute() override;
    std::string name() const override { return "wc"; }

private:
    Mode mode_ = Mode::Words;
};

} // namespace cli

#endif // CLI_WC_COMMAND_H

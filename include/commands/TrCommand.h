#ifndef CLI_TR_COMMAND_H
#define CLI_TR_COMMAND_H

#include "commands/Command.h"

namespace cli {

// tr [argument] -"what" ["with"]
// Replaces every occurrence of the "what" text found in the input stream
// with the "with" text (or simply removes it, if "with" was not given),
// and writes the transformed text to the output stream.
//
// Assumption (documented, see specification "Увод"): the '-' sign that
// introduces "what" is a token of its own, optionally followed by blanks,
// immediately followed by the quoted "what" text; the optional quoted
// "with" text (if present) comes right after it.
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

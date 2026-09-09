#ifndef CLI_FILENAME_COMMAND_H
#define CLI_FILENAME_COMMAND_H

#include "commands/Command.h"

namespace cli {

class FileNameCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;

protected:
    virtual void performAction(const std::string& filename) = 0;
    void execute() override;

    std::string filename_;
};

} // namespace cli

#endif // CLI_FILENAME_COMMAND_H

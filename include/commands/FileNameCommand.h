#ifndef CLI_FILENAME_COMMAND_H
#define CLI_FILENAME_COMMAND_H

#include "commands/Command.h"

namespace cli {

// Common base for touch/truncate/rm: they all take exactly one mandatory
// argument, which is a plain (unquoted) filename, and none of them reads
// or writes a character stream. Factoring the shared argument parsing here
// avoids repeating the same three lines in every subclass and keeps each
// subclass focused on its own single responsibility (creating, clearing or
// removing the file).
class FileNameCommand : public Command {
public:
    void parseArguments(const std::vector<Token>& tokens) override;

protected:
    // Concrete subclasses implement only the actual file-system action.
    virtual void performAction(const std::string& filename) = 0;
    void execute() override;

    std::string filename_;
};

} // namespace cli

#endif // CLI_FILENAME_COMMAND_H

#ifndef CLI_TOUCH_COMMAND_H
#define CLI_TOUCH_COMMAND_H

#include "commands/FileNameCommand.h"

namespace cli {

// touch filename
// Creates an empty file with the given name in the current directory.
// Reports an error (does nothing else) if the file already exists.
class TouchCommand : public FileNameCommand {
public:
    std::string name() const override { return "touch"; }

protected:
    void performAction(const std::string& filename) override;
};

} // namespace cli

#endif // CLI_TOUCH_COMMAND_H

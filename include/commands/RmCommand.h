#ifndef CLI_RM_COMMAND_H
#define CLI_RM_COMMAND_H

#include "commands/FileNameCommand.h"

namespace cli {

// rm filename
// Deletes (removes) the file with the given name.
class RmCommand : public FileNameCommand {
public:
    std::string name() const override { return "rm"; }

protected:
    void performAction(const std::string& filename) override;
};

} // namespace cli

#endif // CLI_RM_COMMAND_H

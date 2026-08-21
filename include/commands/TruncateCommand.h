#ifndef CLI_TRUNCATE_COMMAND_H
#define CLI_TRUNCATE_COMMAND_H

#include "commands/FileNameCommand.h"

namespace cli {

// truncate filename
// Empties the content of an existing file.
class TruncateCommand : public FileNameCommand {
public:
    std::string name() const override { return "truncate"; }

protected:
    void performAction(const std::string& filename) override;
};

} // namespace cli

#endif // CLI_TRUNCATE_COMMAND_H

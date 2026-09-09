#ifndef CLI_BATCH_COMMAND_H
#define CLI_BATCH_COMMAND_H

#include <functional>

#include "commands/Command.h"

namespace cli {

class BatchCommand : public Command {
public:

    using Runner = std::function<void(const std::string&, std::shared_ptr<OutputStream>, std::shared_ptr<OutputStream>)>;

    explicit BatchCommand(Runner runner) : runner_(std::move(runner)) {}

    void parseArguments(const std::vector<Token>& tokens) override;
    void execute() override;
    bool usesOutputStream() const override { return true; }
    std::string name() const override { return "batch"; }

private:
    Runner runner_;
    std::string filename_;
};

} // namespace cli

#endif // CLI_BATCH_COMMAND_H

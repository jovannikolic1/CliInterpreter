#ifndef CLI_BATCH_COMMAND_H
#define CLI_BATCH_COMMAND_H

#include <functional>

#include "commands/Command.h"

namespace cli {

// batch filename
// Interprets the content of 'filename' as a (possibly long) sequence of
// command lines, executing them one after another exactly as if they had
// been typed at the console. Any command line that fails only reports its
// own error and does not stop the rest of the batch. batch may be called
// recursively (batch calling batch); the specification explicitly leaves
// the consequences of that to the user.
//
// Implemented with a callback instead of a direct dependency on the
// Interpreter class, so that Command subclasses stay decoupled from the
// class that drives the read-eval loop.
class BatchCommand : public Command {
public:
    // filename, defaultOutput, defaultError -> runs every line of the file
    using Runner = std::function<void(const std::string&,
                                       std::shared_ptr<OutputStream>,
                                       std::shared_ptr<OutputStream>)>;

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

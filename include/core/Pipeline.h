#ifndef CLI_PIPELINE_H
#define CLI_PIPELINE_H

#include <memory>
#include <vector>

#include "parsing/ParsedCommand.h"
#include "streams/OutputStream.h"

namespace cli {

// Wires the InputStream/OutputStream objects of every stage of a parsed
// pipeline and then runs the stages in order.
//
// Wiring rules (semantic checks, category 4 of "Третман грешака"):
//  - a stage's input can come from (at most) one of: its own argument, an
//    explicit '<' redirection, or the previous stage's output; having more
//    than one of these is a semantic error, and having none while not
//    being the first stage is impossible by construction;
//  - a command with no input stream (time, date, touch, truncate, rm,
//    prompt, batch) may only be the first stage of a pipeline;
//  - a command with no output stream may only be the last stage;
//  - an explicit output redirection is only accepted on the last stage
//    (every earlier stage's output always feeds the next stage);
//  - the error stream of every stage is always the pipeline's default
//    error stream (console, or the batch file's default error stream).
//
// Stages are executed sequentially and their whole output is buffered in
// memory before being handed to the next stage (a StringInputStream). This
// is a deliberate, documented simplification: it keeps the implementation
// single-threaded and simple while still preserving character order, which
// is all the specification requires. The one caveat is that only the
// first stage may sensibly read from the interactive console, which
// matches the specification's own restriction that only the first stage
// of a pipeline may be a stream-less-input command anyway.
class Pipeline {
public:
    Pipeline(std::vector<ParsedCommand> stages,
              std::shared_ptr<OutputStream> defaultOutput,
              std::shared_ptr<OutputStream> defaultError,
              std::shared_ptr<class InputStream> defaultConsoleInput);

    // Wires the streams (throws cli::SemanticError / cli::FileSystemError
    // on failure) and executes every stage in order. Throws
    // cli::CommandExecutionError / cli::FileSystemError if a stage fails
    // while executing.
    void run();

private:
    std::vector<ParsedCommand> stages_;
    std::shared_ptr<OutputStream> defaultOutput_;
    std::shared_ptr<OutputStream> defaultError_;
    std::shared_ptr<InputStream> defaultConsoleInput_;
};

} // namespace cli

#endif // CLI_PIPELINE_H

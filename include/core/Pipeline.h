#ifndef CLI_PIPELINE_H
#define CLI_PIPELINE_H

#include <memory>
#include <vector>

#include "parsing/ParsedCommand.h"
#include "streams/OutputStream.h"

namespace cli {

class Pipeline {
public:
    Pipeline(std::vector<ParsedCommand> stages,std::shared_ptr<OutputStream> defaultOutput,std::shared_ptr<OutputStream> defaultError,std::shared_ptr<class InputStream> defaultConsoleInput);

    void run();

private:
    std::vector<ParsedCommand> stages_;
    std::shared_ptr<OutputStream> defaultOutput_;
    std::shared_ptr<OutputStream> defaultError_;
    std::shared_ptr<InputStream> defaultConsoleInput_;
};

} // namespace cli

#endif // CLI_PIPELINE_H

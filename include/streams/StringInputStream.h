#ifndef CLI_STRING_INPUT_STREAM_H
#define CLI_STRING_INPUT_STREAM_H

#include <string>

#include "streams/InputStream.h"

namespace cli {

// Input stream backed by an in-memory string. Used both for a quoted
// argument ("...") given directly on the command line, and for carrying
// the buffered output of one command into the next one inside a pipeline.
class StringInputStream : public InputStream {
public:
    explicit StringInputStream(std::string content)
        : content_(std::move(content)), position_(0) {}

    bool getChar(char& out) override;
    bool eof() const override;

private:
    std::string content_;
    size_t position_;
};

} // namespace cli

#endif // CLI_STRING_INPUT_STREAM_H

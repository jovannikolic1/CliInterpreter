#ifndef CLI_STRING_OUTPUT_STREAM_H
#define CLI_STRING_OUTPUT_STREAM_H

#include <string>

#include "streams/OutputStream.h"

namespace cli {

// Output stream that simply accumulates every character written to it in
// memory. Used to carry the output of one pipeline stage into the input of
// the next one via a StringInputStream built from getContent().
class StringOutputStream : public OutputStream {
public:
    void putChar(char c) override { buffer_.push_back(c); }

    const std::string& getContent() const { return buffer_; }

private:
    std::string buffer_;
};

} // namespace cli

#endif // CLI_STRING_OUTPUT_STREAM_H

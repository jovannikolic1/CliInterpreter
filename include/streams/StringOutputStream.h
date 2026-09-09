#ifndef CLI_STRING_OUTPUT_STREAM_H
#define CLI_STRING_OUTPUT_STREAM_H

#include <string>

#include "streams/OutputStream.h"

namespace cli {

class StringOutputStream : public OutputStream {
public:
    void putChar(char c) override { buffer_.push_back(c); }

    const std::string& getContent() const { return buffer_; }

private:
    std::string buffer_;
};

} // namespace cli

#endif // CLI_STRING_OUTPUT_STREAM_H

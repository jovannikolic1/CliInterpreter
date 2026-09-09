#ifndef CLI_OUTPUT_STREAM_H
#define CLI_OUTPUT_STREAM_H

#include <string>
#include <iostream>

namespace cli {

class OutputStream {
public:
    virtual ~OutputStream() = default;

    virtual void putChar(char c) = 0;

    virtual void putString(const std::string& s) {
        for (char c : s) putChar(c);

    }
};

} // namespace cli

#endif // CLI_OUTPUT_STREAM_H

#ifndef CLI_OUTPUT_STREAM_H
#define CLI_OUTPUT_STREAM_H

#include <string>
#include <iostream>

namespace cli {

// Abstraction over "the output character stream of a command" (and, reused
// with the same interface, over its error stream). Concrete commands only
// write through this interface, so they do not need to know whether their
// result ends up on the console, in a file, or feeding the next command of
// a pipeline.
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

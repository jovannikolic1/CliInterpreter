#ifndef CLI_INPUT_STREAM_H
#define CLI_INPUT_STREAM_H

#include <string>

namespace cli {

class InputStream {
public:
    virtual ~InputStream() = default;

    virtual bool getChar(char& out) = 0;

    virtual std::string readAll();

    virtual bool eof() const = 0;
};

} // namespace cli

#endif // CLI_INPUT_STREAM_H

#ifndef CLI_INPUT_STREAM_H
#define CLI_INPUT_STREAM_H

#include <string>

namespace cli {

// Abstraction over "the input character stream of a command", which,
// depending on how the command was invoked, can be the console, a quoted
// argument, a file, or (inside a pipeline) the output of the previous
// command. Concrete commands only ever talk to this interface, which keeps
// them decoupled from where their characters actually come from.
class InputStream {
public:
    virtual ~InputStream() = default;

    // Reads the next character into 'out'. Returns false (and leaves 'out'
    // unchanged) once the stream is exhausted.
    virtual bool getChar(char& out) = 0;

    // Convenience: reads every remaining character into a single string.
    virtual std::string readAll();

    // True once no more characters are available.
    virtual bool eof() const = 0;
};

} // namespace cli

#endif // CLI_INPUT_STREAM_H

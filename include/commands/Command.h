#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include <memory>
#include <string>
#include <vector>

#include "parsing/Token.h"
#include "streams/InputStream.h"
#include "streams/OutputStream.h"

namespace cli {

class Command {
public:
    virtual ~Command() = default;

    virtual void parseArguments(const std::vector<Token>& tokens) = 0;

    virtual bool usesInputStream() const { return false; }

    virtual bool usesOutputStream() const { return false; }

    virtual bool argumentDefinesInput() const { return usesInputStream(); }

    void setInputStream(std::shared_ptr<InputStream> in) { input_ = std::move(in); }
    void setOutputStream(std::shared_ptr<OutputStream> out) { output_ = std::move(out); }
    void setErrorStream(std::shared_ptr<OutputStream> err) { error_ = std::move(err); }

    std::shared_ptr<InputStream> getInputStream() const { return input_; }
    std::shared_ptr<OutputStream> getOutputStream() const { return output_; }
    std::shared_ptr<OutputStream> getErrorStream() const { return error_; }

    virtual void execute() = 0;

    virtual std::string name() const = 0;

    bool hasOwnArgument() const { return hasOwnArgument_; }

    bool isOwnArgumentQuoted() const { return argumentIsQuoted_; }

    const std::string& getOwnArgumentText() const { return argumentText_; }

protected:
    void setOwnArgument(std::string text, bool quoted) {
        argumentText_ = std::move(text);
        argumentIsQuoted_ = quoted;
        hasOwnArgument_ = true;
    }

    std::shared_ptr<InputStream> input_;
    std::shared_ptr<OutputStream> output_;
    std::shared_ptr<OutputStream> error_;

private:
    bool hasOwnArgument_ = false;
    bool argumentIsQuoted_ = false;
    std::string argumentText_;
};

} // namespace cli

#endif // CLI_COMMAND_H

#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include <memory>
#include <string>
#include <vector>

#include "parsing/Token.h"
#include "streams/InputStream.h"
#include "streams/OutputStream.h"

namespace cli {

// Common base class for every supported shell command (echo, wc, tr, ...).
//
// A Command is used in two phases:
//   1. parseArguments() consumes the tokens that follow the command name
//      on the command line (options, argument, but NOT the trailing
//      redirection, which the Parser strips off beforehand) and stores
//      whatever the concrete command needs to do its job. Syntax mistakes
//      are reported by throwing cli::SyntaxError.
//   2. execute() actually performs the command's job, reading from
//      getInputStream() (if usesInputStream() is true) and writing to
//      getOutputStream()/getErrorStream().
//
// Splitting parsing and execution into two virtual methods, one per
// concrete subclass, keeps every command's own little grammar local to its
// own class instead of scattered across a big switch statement.
class Command {
public:
    virtual ~Command() = default;

    // --- parsing -------------------------------------------------------
    virtual void parseArguments(const std::vector<Token>& tokens) = 0;

    // Does this command read a character stream at all? (time/date do not;
    // touch/truncate/rm/prompt/batch work with filenames or plain
    // arguments, not a character stream).
    virtual bool usesInputStream() const { return false; }

    // Does this command produce a character stream as its result?
    virtual bool usesOutputStream() const { return false; }

    // True if the command's own argument (quoted text or filename) can, by
    // itself, define its input stream (echo, wc, tr, head). Needed by the
    // parser to detect the semantic clash of argument + redirection.
    virtual bool argumentDefinesInput() const { return usesInputStream(); }

    // --- wiring of the streams (done by the Parser / Interpreter) ------
    void setInputStream(std::shared_ptr<InputStream> in) { input_ = std::move(in); }
    void setOutputStream(std::shared_ptr<OutputStream> out) { output_ = std::move(out); }
    void setErrorStream(std::shared_ptr<OutputStream> err) { error_ = std::move(err); }

    std::shared_ptr<InputStream> getInputStream() const { return input_; }
    std::shared_ptr<OutputStream> getOutputStream() const { return output_; }
    std::shared_ptr<OutputStream> getErrorStream() const { return error_; }

    // --- execution -------------------------------------------------------
    // Throws cli::CommandExecutionError / cli::FileSystemError on failure.
    virtual void execute() = 0;

    // Human readable command name, used for diagnostics.
    virtual std::string name() const = 0;

    // --- own-argument-as-input bookkeeping ------------------------------
    // For commands whose own argument can define their input stream
    // (echo, wc, tr, head): after parseArguments() runs, these report
    // whether such an argument was actually given, whether it was a quoted
    // literal or a bare filename, and its text. The Parser uses this to
    // wire the right InputStream and to detect the semantic clash of an
    // own argument together with an explicit '<' redirection.
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

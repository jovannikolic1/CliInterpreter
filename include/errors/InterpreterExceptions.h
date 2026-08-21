#ifndef CLI_INTERPRETER_EXCEPTIONS_H
#define CLI_INTERPRETER_EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <vector>

namespace cli {

// Base class for every error that the interpreter can report to the user.
// Every concrete exception carries a human readable message that is ready
// to be printed as-is on the error stream.
class InterpreterException : public std::runtime_error {
public:
    explicit InterpreterException(const std::string& message)
        : std::runtime_error(message) {}
};

// Raised while scanning raw characters of a command line (Lexer), e.g. an
// unexpected/forbidden character was found outside of a quoted argument.
// Keeps the positions of the offending characters so the interpreter can
// draw a caret ('^') line under the original input, as suggested by the
// project specification.
class LexicalError : public InterpreterException {
public:
    LexicalError(const std::string& message, std::vector<size_t> badPositions)
        : InterpreterException(message), positions(std::move(badPositions)) {}

    const std::vector<size_t>& getPositions() const { return positions; }

private:
    std::vector<size_t> positions;
};

// Raised while turning a token sequence into a command / pipeline, e.g. a
// command was given an argument in a format it does not understand, a
// mandatory option is missing, redirection appears in the middle of a
// command, etc.
class SyntaxError : public InterpreterException {
public:
    explicit SyntaxError(const std::string& message)
        : InterpreterException(message) {}
};

// Raised for an unrecognized command name, using exactly the message format
// requested by the specification: "Unknown command: <name>".
class UnknownCommandError : public InterpreterException {
public:
    explicit UnknownCommandError(const std::string& commandName)
        : InterpreterException("Unknown command: " + commandName) {}
};

// Raised when a command line is syntactically valid but semantically
// inconsistent, e.g. a command that already has an argument-defined input
// stream is also given an input redirection, or a command with no input
// stream is placed in the middle of a pipeline.
class SemanticError : public InterpreterException {
public:
    explicit SemanticError(const std::string& message)
        : InterpreterException(message) {}
};

// Raised for errors that happen while a command is actually executing
// (category 5 from the specification: a semantic error specific to a
// command, e.g. "tr" with no "what" text, "head" with an invalid count...).
class CommandExecutionError : public InterpreterException {
public:
    explicit CommandExecutionError(const std::string& message)
        : InterpreterException(message) {}
};

// Raised when the underlying operating system reports a problem while a
// command works with the file system (category 6): file does not exist,
// file already exists, no permission, etc.
class FileSystemError : public InterpreterException {
public:
    explicit FileSystemError(const std::string& message)
        : InterpreterException(message) {}
};

} // namespace cli

#endif // CLI_INTERPRETER_EXCEPTIONS_H

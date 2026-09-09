#ifndef CLI_INTERPRETER_EXCEPTIONS_H
#define CLI_INTERPRETER_EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <vector>

namespace cli {

class InterpreterException : public std::runtime_error {
public:
    explicit InterpreterException(const std::string& message)
        : std::runtime_error(message) {}
};

class LexicalError : public InterpreterException {
public:
    LexicalError(const std::string& message, std::vector<size_t> badPositions)
        : InterpreterException(message), positions(std::move(badPositions)) {}

    const std::vector<size_t>& getPositions() const { return positions; }

private:
    std::vector<size_t> positions;
};

class SyntaxError : public InterpreterException {
public:
    explicit SyntaxError(const std::string& message)
        : InterpreterException(message) {}
};

class UnknownCommandError : public InterpreterException {
public:
    explicit UnknownCommandError(const std::string& commandName)
        : InterpreterException("Unknown command: " + commandName) {}
};

class SemanticError : public InterpreterException {
public:
    explicit SemanticError(const std::string& message)
        : InterpreterException(message) {}
};

class CommandExecutionError : public InterpreterException {
public:
    explicit CommandExecutionError(const std::string& message)
        : InterpreterException(message) {}
};

class FileSystemError : public InterpreterException {
public:
    explicit FileSystemError(const std::string& message)
        : InterpreterException(message) {}
};

} // namespace cli

#endif // CLI_INTERPRETER_EXCEPTIONS_H

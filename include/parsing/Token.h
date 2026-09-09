#ifndef CLI_TOKEN_H
#define CLI_TOKEN_H

#include <string>

namespace cli {

enum class TokenType {
    Word,
    Quoted,
    Pipe,       // '|'
    Less,       // '<'
    Greater,    // '>'
    DGreater    // '>>'
};

class Token {
public:
    Token(TokenType type, std::string text, size_t position)
        : type_(type), text_(std::move(text)), position_(position) {}

    TokenType getType() const { return type_; }
    const std::string& getText() const { return text_; }
    size_t getPosition() const { return position_; }

    bool isWord() const { return type_ == TokenType::Word; }
    bool isQuoted() const { return type_ == TokenType::Quoted; }
    bool isRedirection() const {
        return type_ == TokenType::Less || type_ == TokenType::Greater ||
               type_ == TokenType::DGreater;
    }

private:
    TokenType type_;
    std::string text_;
    size_t position_;
};

} // namespace cli

#endif // CLI_TOKEN_H

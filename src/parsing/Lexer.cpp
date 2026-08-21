#include "parsing/Lexer.h"

#include <cctype>

#include "errors/InterpreterExceptions.h"

namespace cli {
    bool Lexer::isBlank(char c) {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

bool Lexer::isWordChar(char c) {
    if (std::isalnum(static_cast<unsigned char>(c))) return true;
    switch (c) {
        case '_': case '.': case '-': case '/': case ':': case '\\':
            return true;
        default:
            return false;
    }
}

std::vector<Token> Lexer::tokenize(const std::string& line) const {
    std::vector<Token> tokens;
    std::vector<size_t> badPositions;

    size_t i = 0;
    const size_t n = line.size();

    while (i < n) {
        char c = line[i];

        if (isBlank(c)) {
            ++i;
            continue;
        }

        if (c == '"') {
            size_t start = i;
            ++i; // skip opening quote
            std::string content;
            bool closed = false;
            while (i < n) {
                if (line[i] == '"') {
                    closed = true;
                    ++i; // skip closing quote
                    break;
                }
                if (line[i] == '\n') break; // never happens, line has no '\n'
                content.push_back(line[i]);
                ++i;
            }
            if (!closed) {
                throw LexicalError("Error - unterminated quoted string starting at:",
                                    std::vector<size_t>{start});
            }
            tokens.emplace_back(TokenType::Quoted, content, start);
            continue;
        }

        if (c == '|') {
            tokens.emplace_back(TokenType::Pipe, "|", i);
            ++i;
            continue;
        }

        if (c == '<') {
            tokens.emplace_back(TokenType::Less, "<", i);
            ++i;
            continue;
        }

        if (c == '>') {
            if (i + 1 < n && line[i + 1] == '>') {
                tokens.emplace_back(TokenType::DGreater, ">>", i);
                i += 2;
            } else {
                tokens.emplace_back(TokenType::Greater, ">", i);
                ++i;
            }
            continue;
        }

        if (isWordChar(c)) {
            size_t start = i;
            std::string content;
            while (i < n && isWordChar(line[i])) {
                content.push_back(line[i]);
                ++i;
            }
            tokens.emplace_back(TokenType::Word, content, start);
            continue;
        }

        // Character not allowed at this position: record it and keep
        // scanning so the caller can report every bad character at once.
        badPositions.push_back(i);
        ++i;
    }

    if (!badPositions.empty()) {
        throw LexicalError("Error - unexpected characters:", badPositions);
    }

    return tokens;
}

} // namespace cli

#ifndef CLI_LEXER_H
#define CLI_LEXER_H

#include <string>
#include <vector>

#include "parsing/Token.h"

namespace cli {

class Lexer {
public:

    std::vector<Token> tokenize(const std::string& line) const;

    static bool isWordChar(char c);

    static bool isBlank(char c);
};

} // namespace cli

#endif // CLI_LEXER_H

#ifndef CLI_LEXER_H
#define CLI_LEXER_H

#include <string>
#include <vector>

#include "parsing/Token.h"

namespace cli {

// Turns one raw command line (already trimmed to at most 512 characters, as
// required by the specification) into a sequence of Tokens.
//
// Lexical rules implemented (see the project specification):
//  - letters are case sensitive;
//  - tokens are separated by "blanks" (spaces and horizontal tabs);
//  - a "..."-quoted fragment is a single token whose text is taken
//    literally (no character has special meaning inside it, except the
//    closing quote itself);
//  - '|', '<' and '>' (and the pair ">>") are special tokens outside of
//    quotes;
//  - any other character that is not allowed at the position where it is
//    found is a lexical error.
//
// Assumption (the specification leaves this open, see "Увод"): outside of
// quoted fragments, an unquoted Word token may contain letters, digits and
// the punctuation characters commonly used in identifiers and file paths
// ('_', '.', '-', '/', ':', '\\'). Any other character found outside a
// quoted fragment (e.g. '&', '*', '+', '?', ...) is reported as a lexical
// error, matching the example given in the specification.
class Lexer {
public:
    // Tokenizes 'line'. Throws cli::LexicalError, collecting the positions
    // of every offending character, if the line does not comply with the
    // lexical rules (unterminated quote, forbidden character, ...).
    std::vector<Token> tokenize(const std::string& line) const;

    // Returns true if 'c' is a character allowed to appear (unescaped,
    // outside of quotes) inside a Word token.
    static bool isWordChar(char c);

    // Returns true if 'c' is considered a blank by the lexical rules
    // (space or horizontal tab).
    static bool isBlank(char c);
};

} // namespace cli

#endif // CLI_LEXER_H

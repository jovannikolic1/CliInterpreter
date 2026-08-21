#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <vector>

#include "commands/CommandFactory.h"
#include "parsing/ParsedCommand.h"
#include "parsing/Token.h"

namespace cli {

// Turns a token sequence (as produced by the Lexer for one command line)
// into a sequence of ParsedCommand pipeline stages.
//
// Responsibilities:
//  - split the tokens into stages at top-level '|' tokens;
//  - for each stage, strip off any trailing redirection ('<file',
//    '>file', '>>file', in any order, at most one of each) and remember it;
//  - look up the command name (first remaining token) through the
//    CommandFactory and let the resulting Command parse its own
//    option/argument tokens.
//
// Throws cli::SyntaxError / cli::UnknownCommandError on malformed input.
// (Cross-stage semantic checks, e.g. "only the last stage may redirect its
// output", are done afterwards by the Pipeline class, since they need the
// full picture of the pipeline.)
class Parser {
public:
    explicit Parser(const CommandFactory& factory) : factory_(factory) {}

    std::vector<ParsedCommand> parse(const std::vector<Token>& tokens) const;

private:
    static std::vector<std::vector<Token>> splitOnPipes(const std::vector<Token>& tokens);
    static ParsedCommand parseStage(const std::vector<Token>& stageTokens, const CommandFactory& factory);

    const CommandFactory& factory_;
};

} // namespace cli

#endif // CLI_PARSER_H

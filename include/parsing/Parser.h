#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <vector>

#include "commands/CommandFactory.h"
#include "parsing/ParsedCommand.h"
#include "parsing/Token.h"

namespace cli {

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

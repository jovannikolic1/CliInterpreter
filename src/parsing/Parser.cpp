#include "parsing/Parser.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

std::vector<std::vector<Token>> Parser::splitOnPipes(const std::vector<Token>& tokens) {
    std::vector<std::vector<Token>> stages;
    std::vector<Token> current;

    for (const Token& t : tokens) {
        if (t.getType() == TokenType::Pipe) {
            if (current.empty()) {
                throw SyntaxError("Syntax error: empty command before or after '|'");
            }
            stages.push_back(current);
            current.clear();
        } else {
            current.push_back(t);
        }
    }

    if (current.empty()) {
        throw SyntaxError("Syntax error: empty command before or after '|'");
    }
    stages.push_back(current);

    return stages;
}

ParsedCommand Parser::parseStage(const std::vector<Token>& stageTokensIn, const CommandFactory& factory) {
    std::vector<Token> stageTokens = stageTokensIn;
    ParsedCommand parsed;

    // Strip trailing redirection clauses (in any order, at most one input
    // and one output), as required by the specification.
    while (stageTokens.size() >= 2) {
        const Token& symbol = stageTokens[stageTokens.size() - 2];
        const Token& fileTok = stageTokens.back();

        if (!symbol.isRedirection() || !fileTok.isWord()) break;

        if (symbol.getType() == TokenType::Less) {
            if (parsed.inputRedirectFile.has_value()) {
                throw SyntaxError("Syntax error: multiple input redirections");
            }
            parsed.inputRedirectFile = fileTok.getText();
        } else {
            if (parsed.outputRedirectFile.has_value()) {
                throw SyntaxError("Syntax error: multiple output redirections");
            }
            parsed.outputRedirectFile = fileTok.getText();
            parsed.appendOutput = (symbol.getType() == TokenType::DGreater);
        }

        stageTokens.pop_back();
        stageTokens.pop_back();
    }

    // Anything left that is still a redirection/pipe token is misplaced.
    for (const Token& t : stageTokens) {
        if (t.isRedirection()) {
            throw SyntaxError("Syntax error: redirection allowed only at the end of a command");
        }
    }

    if (stageTokens.empty() || !stageTokens.front().isWord()) {
        throw SyntaxError("Syntax error: expected a command name");
    }

    const std::string commandName = stageTokens.front().getText();
    std::vector<Token> argTokens(stageTokens.begin() + 1, stageTokens.end());

    parsed.command = factory.create(commandName); // may throw UnknownCommandError
    parsed.command->parseArguments(argTokens);     // may throw SyntaxError

    return parsed;
}

std::vector<ParsedCommand> Parser::parse(const std::vector<Token>& tokens) const {
    std::vector<ParsedCommand> result;
    for (const auto& stageTokens : splitOnPipes(tokens)) {
        result.push_back(parseStage(stageTokens, factory_));
    }
    return result;
}

} // namespace cli

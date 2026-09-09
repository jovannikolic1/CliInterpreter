#include "commands/HeadCommand.h"

#include <cctype>

#include "errors/InterpreterExceptions.h"

namespace cli {

void HeadCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.empty() || !tokens[0].isWord() ||
        tokens[0].getText().size() < 3 ||
        tokens[0].getText()[0] != '-' || tokens[0].getText()[1] != 'n') {
        throw SyntaxError("head: expected mandatory -ncount option");
    }

    const std::string& opt = tokens[0].getText();
    std::string digits = opt.substr(2);
    if (digits.empty() || digits.size() > 5 ||
        digits.find_first_not_of("0123456789") != std::string::npos) {
        throw SyntaxError("head: -n must be followed by at most 5 decimal digits");
    }
    count_ = std::stoi(digits);

    if (tokens.size() > 2) {
        throw SyntaxError("head: too many arguments");
    }
    if (tokens.size() == 2) {
        const Token& t = tokens[1];
        if (t.isQuoted()) {
            setOwnArgument(t.getText(), true);
        } else if (t.isWord()) {
            setOwnArgument(t.getText(), false);
        } else {
            throw SyntaxError("head: invalid argument");
        }
    }
}

void HeadCommand::execute() {
        const std::string text = input_->readAll();

        int linesLeft = count_;
        size_t i = 0;
        while (linesLeft > 0 && i < text.size()) {
            char c = text[i++];
            output_->putChar(c);
            if (c == '\n') --linesLeft;
        }
}

} // namespace cli

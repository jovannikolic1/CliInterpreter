#include "commands/WcCommand.h"

#include <cctype>

#include "errors/InterpreterExceptions.h"

namespace cli {

void WcCommand::parseArguments(const std::vector<Token>& tokens) {
    if (tokens.empty() || !tokens[0].isWord() ||
        (tokens[0].getText() != "-w" && tokens[0].getText() != "-c")) {
        throw SyntaxError("wc: expected -w or -c option");
    }
    mode_ = (tokens[0].getText() == "-w") ? Mode::Words : Mode::Chars;

    if (tokens.size() > 2) {
        throw SyntaxError("wc: too many arguments");
    }
    if (tokens.size() == 2) {
        const Token& t = tokens[1];
        if (t.isQuoted()) {
            setOwnArgument(t.getText(), true);
        } else if (t.isWord()) {
            setOwnArgument(t.getText(), false);
        } else {
            throw SyntaxError("wc: invalid argument");
        }
    }
}

void WcCommand::execute() {
    long count = 0;
    char c;
    bool inWord = false;

    if (mode_ == Mode::Chars) {
        while (input_->getChar(c)) ++count;
    } else {
        while (input_->getChar(c)) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                inWord = false;
            } else if (!inWord) {
                inWord = true;
                ++count;
            }
        }
    }
    output_->putString(std::to_string(count)+" ");
}

} // namespace cli

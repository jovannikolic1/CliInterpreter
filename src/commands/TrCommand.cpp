#include "commands/TrCommand.h"

#include "errors/InterpreterExceptions.h"

namespace cli {

namespace {
bool isDashMarker(const Token& t) {
    return t.isWord() && t.getText() == "-";
}
} // namespace

void TrCommand::parseArguments(const std::vector<Token>& tokens) {
    size_t idx = 0;

    if (tokens.empty()) {
        throw SyntaxError("tr: missing -\"what\" part");
    }

    if (!isDashMarker(tokens[0])) {
        const Token& t = tokens[0];
        if (t.isQuoted()) {
            setOwnArgument(t.getText(), true);
        } else if (t.isWord()) {
            setOwnArgument(t.getText(), false);
        } else {
            throw SyntaxError("tr: invalid argument");
        }
        idx = 1;
    }

    if (idx >= tokens.size() || !isDashMarker(tokens[idx])) {
        throw SyntaxError("tr: expected -\"what\"");
    }
    ++idx;

    if (idx >= tokens.size() || !tokens[idx].isQuoted()) {
        throw SyntaxError("tr: expected quoted \"what\" text after '-'");
    }
    what_ = tokens[idx].getText();
    ++idx;

    if (idx < tokens.size()) {
        if (!tokens[idx].isQuoted()) {
            throw SyntaxError("tr: expected quoted \"with\" text");
        }
        with_ = tokens[idx].getText();
        hasWith_ = true;
        ++idx;
    }

    if (idx != tokens.size()) {
        throw SyntaxError("tr: too many arguments");
    }

    if (what_.empty()) {
        throw CommandExecutionError("tr: \"what\" text must not be empty");
    }
}

void TrCommand::execute() {
    std::string text = input_->readAll();
    std::string result;
    result.reserve(text.size());

    const std::string replacement = hasWith_ ? with_ : std::string();

    size_t i = 0;
    while (i < text.size()) {
        if (text.compare(i, what_.size(), what_) == 0) {
            result += replacement;
            i += what_.size();
        } else {
            result.push_back(text[i]);
            ++i;
        }
    }

    output_->putString(result);
}

} // namespace cli

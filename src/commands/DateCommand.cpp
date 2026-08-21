#include "commands/DateCommand.h"

#include <ctime>
#include <iomanip>
#include <sstream>

#include "errors/InterpreterExceptions.h"

namespace cli {

void DateCommand::parseArguments(const std::vector<Token>& tokens) {
    if (!tokens.empty()) {
        throw SyntaxError("date: does not accept any argument");
    }
}

void DateCommand::execute() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    output_->putString(oss.str());
}

} // namespace cli

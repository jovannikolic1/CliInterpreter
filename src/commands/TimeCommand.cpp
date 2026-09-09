#include "commands/TimeCommand.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include "errors/InterpreterExceptions.h"

namespace cli {

void TimeCommand::parseArguments(const std::vector<Token>& tokens) {
    if (!tokens.empty()) {
        throw SyntaxError("time: does not accept any argument");
    }
}

void TimeCommand::execute() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
#if defined(_WIN32)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%H:%M:%S");
    output_->putString(oss.str());
}

} // namespace cli

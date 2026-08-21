#include "core/Pipeline.h"

#include "errors/InterpreterExceptions.h"
#include "streams/FileInputStream.h"
#include "streams/FileOutputStream.h"
#include "streams/StringInputStream.h"
#include "streams/StringOutputStream.h"

namespace cli {

Pipeline::Pipeline(std::vector<ParsedCommand> stages,
                    std::shared_ptr<OutputStream> defaultOutput,
                    std::shared_ptr<OutputStream> defaultError,
                    std::shared_ptr<InputStream> defaultConsoleInput)
    : stages_(std::move(stages)),
      defaultOutput_(std::move(defaultOutput)),
      defaultError_(std::move(defaultError)),
      defaultConsoleInput_(std::move(defaultConsoleInput)) {}

void Pipeline::run() {
    const size_t stageCount = stages_.size();
    std::shared_ptr<StringOutputStream> previousBuffer; // output of the previous stage

    for (size_t i = 0; i < stageCount; ++i) {
        ParsedCommand& stage = stages_[i];
        Command& cmd = *stage.command;
        const bool isFirst = (i == 0);
        const bool isLast = (i == stageCount - 1);

        cmd.setErrorStream(defaultError_);

        // ---------------- input wiring ----------------
        int inputSourceCount = (cmd.hasOwnArgument() ? 1 : 0) +
                                (stage.inputRedirectFile.has_value() ? 1 : 0) +
                                (!isFirst ? 1 : 0);

        if (!cmd.usesInputStream()) {
            if (!isFirst) {
                throw SemanticError(cmd.name() +
                    ": has no input stream, so it cannot appear other than "
                    "first in a pipeline");
            }
            if (stage.inputRedirectFile.has_value()) {
                throw SemanticError(cmd.name() +
                    ": does not read an input stream, '<' redirection is not allowed");
            }
        } else {
            if (inputSourceCount > 1) {
                throw SemanticError(cmd.name() +
                    ": input stream is defined more than once (argument, "
                    "'<' redirection and/or pipe)");
            }
            if (cmd.hasOwnArgument()) {
                if (cmd.isOwnArgumentQuoted()) {
                    cmd.setInputStream(std::make_shared<StringInputStream>(cmd.getOwnArgumentText()));
                } else {
                    cmd.setInputStream(std::make_shared<FileInputStream>(cmd.getOwnArgumentText()));
                }
            } else if (stage.inputRedirectFile.has_value()) {
                cmd.setInputStream(std::make_shared<FileInputStream>(*stage.inputRedirectFile));
            } else if (!isFirst) {
                cmd.setInputStream(std::make_shared<StringInputStream>(previousBuffer->getContent()));
            } else {
                cmd.setInputStream(defaultConsoleInput_);
            }
        }

        // ---------------- output wiring ----------------
        if (!cmd.usesOutputStream()) {
            if (!isLast) {
                throw SemanticError(cmd.name() +
                    ": has no output stream, so it cannot appear other than "
                    "last in a pipeline");
            }
            if (stage.outputRedirectFile.has_value()) {
                throw SemanticError(cmd.name() +
                    ": does not produce an output stream, redirection is not allowed");
            }
            cmd.setOutputStream(defaultOutput_);
        } else {
            if (stage.outputRedirectFile.has_value() && !isLast) {
                throw SemanticError(cmd.name() +
                    ": output redirection is only allowed on the last command of a pipeline");
            }
            if (isLast) {
                if (stage.outputRedirectFile.has_value()) {
                    cmd.setOutputStream(std::make_shared<FileOutputStream>(
                        *stage.outputRedirectFile, stage.appendOutput));
                } else {
                    cmd.setOutputStream(defaultOutput_);
                }
            } else {
                auto buffer = std::make_shared<StringOutputStream>();
                cmd.setOutputStream(buffer);
                previousBuffer = buffer;
            }
        }

        cmd.execute();
    }
}

} // namespace cli

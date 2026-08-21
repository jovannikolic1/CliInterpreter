# CLI Interpreter — OOP Project (OOP1, 2025/2026)

A simplified command-line interpreter (CLI) implemented in C++17, following
the full project specification ("Пројектни задатак", v1.02) — both Phase 1
and Phase 2 requirements: `echo`, `prompt`, `time`, `date`, `touch`,
`truncate`, `rm`, `wc`, `tr`, `head`, `batch`, input/output redirection
(`<`, `>`, `>>`) and pipes (`|`), together with the required lexical /
syntax / semantic error handling.

## Building

Requires a C++17 compiler. Two options:

```bash
# Option A: CMake
mkdir -p build && cd build
cmake ..
make

# Option B: plain g++ (no CMake needed)
g++ -std=c++17 -Wall -Wextra -Iinclude $(find src -name '*.cpp') -o build/cli_interpreter
```

Run it with `./build/cli_interpreter`.

## Folder layout

```
cli-interpreter/
├── CMakeLists.txt
├── README.md
├── include/                 (headers, mirrors src/)
│   ├── errors/               InterpreterExceptions.h
│   ├── parsing/               Token.h, Lexer.h, Parser.h, ParsedCommand.h
│   ├── streams/                InputStream/OutputStream and their
│   │                            Console/String/File implementations
│   ├── commands/               Command (abstract) + one class per command
│   │                            + CommandFactory
│   └── core/                   Interpreter, Pipeline
├── src/                      (implementation, same sub-folders as include/)
└── tests/                    (place for local ad-hoc test scripts)
```

## Architectural overview

| Layer | Responsibility |
|---|---|
| `Lexer` | Turns one raw command line into a list of `Token`s, applying the lexical rules (quoting, blanks, `\|`/`<`/`>`/`>>`), reporting `LexicalError` with the offending column(s). |
| `Parser` | Splits tokens into pipeline stages at top-level `\|`, strips trailing redirection (`<file`, `>file`, `>>file`) per stage, looks the command name up in `CommandFactory`, and lets the concrete `Command` parse its own option/argument tokens (`SyntaxError`, `UnknownCommandError`). |
| `Command` (+ subclasses) | One class per command (`EchoCommand`, `WcCommand`, `TrCommand`, `HeadCommand`, `TouchCommand`, `TruncateCommand`, `RmCommand`, `TimeCommand`, `DateCommand`, `PromptCommand`, `BatchCommand`). Each knows only its own grammar and its own job; it talks to its input/output/error only through the `InputStream`/`OutputStream` interfaces. `TouchCommand`/`TruncateCommand`/`RmCommand` share a `FileNameCommand` base (single mandatory filename argument). |
| `InputStream` / `OutputStream` | Abstract character-stream interfaces, with `Console...`, `String...` and `File...` implementations, so a `Command` never needs to know whether it is talking to the keyboard, a quoted literal, a file, or the previous/next stage of a pipe. |
| `Pipeline` | Given the parsed stages of one command line, wires each stage's actual streams (detecting the semantic errors of category 4: input/output defined more than once, a stream-less command used in the wrong position, ...) and runs the stages in order. |
| `Interpreter` | Owns the read/print loop (prompt, 512-character line limit), turns a line into an executed pipeline via `Lexer`+`Parser`+`Pipeline`, and reports any exception on the error stream. Also drives `batch` files through `runBatchFile()`. |

Every error type from the specification maps to one C++ exception class in
`errors/InterpreterExceptions.h`: `LexicalError`, `SyntaxError`,
`UnknownCommandError`, `SemanticError`, `CommandExecutionError`,
`FileSystemError`. `Interpreter::executeLine()` is the single place that
catches them and turns them into the printed error message, so every
command/parsing stage stays free of console-formatting concerns.

## Documented assumptions

The specification explicitly invites the student to introduce and document
reasonable assumptions wherever it is not fully precise. The ones made
here:

1. **Allowed characters in an unquoted word.** Outside quotes, a `Word`
   token (command name, option, filename, ...) may contain letters,
   digits, and `_ . - / : \`. Any other character found outside a quoted
   fragment (e.g. `&`, `*`, `+`, `?`) is a lexical error — matching the
   example given in the specification (`wc& -w *"..." +?`).
2. **`tr` grammar.** The format `tr [argument] –what [with]` is parsed as:
   an optional argument token, then a `Word` token that is exactly `-`,
   then a mandatory quoted `"what"` token, then an optional quoted
   `"with"` token.
3. **Filenames are unquoted.** `touch`, `truncate`, `rm` and `batch` take
   their filename as a plain (unquoted) word, consistently with every
   filename example in the specification (e.g. `input.txt`).
4. **Pipeline execution model.** Each stage runs to completion and its
   entire output is buffered in memory before being handed to the next
   stage as its input (rather than truly interleaving execution
   character-by-character across concurrent stages). Character order is
   fully preserved, which is all the specification requires; this keeps
   the implementation single-threaded and simple.
5. **`batch` and interactive missing arguments.** The specification asks
   that, inside a batch file, a command missing a mandatory *plain*
   argument (e.g. `touch` with no filename) and first in its pipeline
   should read that argument from the console instead of failing. This
   implementation reports a syntax error in that case instead, exactly as
   it would at the top level — a deliberate, documented simplification.
   Commands whose *input character stream* falls back to the console
   (e.g. `wc -w` with no argument/redirect) already transparently read
   from the real console even inside a batch file, since `runBatchFile()`
   reuses the interpreter's own console input stream as the pipeline's
   default input.
6. **Console EOF (Ctrl+D / Ctrl+Z) is per-command, not permanent.** After a
   command that reads its input from the console reaches the
   operating-system EOF sequence, the interpreter clears the stream's
   EOF/fail state so that the next prompt can keep reading from the
   console normally.

## Notes on grading criteria

* Style: 4-space indentation, `PascalCase` for classes, `camelCase` for
  methods/variables, one header/implementation pair per class, comments
  explain *why*, not *what*.
* Object decomposition: `Command` is a small abstract interface with one
  focused subclass per command; stream handling is fully decoupled from
  both parsing and command logic via `InputStream`/`OutputStream`;
  `PromptCommand`/`BatchCommand` depend on the `Interpreter` only through
  `std::function` callbacks passed in by `CommandFactory`, avoiding a
  circular dependency between `commands/` and `core/`.
* C++/OOP techniques used where they are actually useful: virtual
  dispatch + RAII (streams close themselves via destructors), a custom
  exception hierarchy, smart pointers (`std::unique_ptr`/`std::shared_ptr`)
  for ownership instead of raw `new`/`delete`, `std::function` for
  dependency injection instead of a hard dependency.

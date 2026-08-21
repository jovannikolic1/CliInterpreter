#ifndef CLI_FILE_INPUT_STREAM_H
#define CLI_FILE_INPUT_STREAM_H

#include <fstream>
#include <string>

#include "streams/InputStream.h"

namespace cli {

// Input stream that reads the content of a text file, character by
// character. Used both when a command's own argument names a file, and
// when its input is explicitly redirected from a file with '<'.
class FileInputStream : public InputStream {
public:
    // Throws cli::FileSystemError if the file cannot be opened.
    explicit FileInputStream(const std::string& filename);

    bool getChar(char& out) override;
    bool eof() const override;

private:
    std::ifstream file_;
    std::string filename_;
};

} // namespace cli

#endif // CLI_FILE_INPUT_STREAM_H

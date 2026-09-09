#ifndef CLI_FILE_INPUT_STREAM_H
#define CLI_FILE_INPUT_STREAM_H

#include <fstream>
#include <string>

#include "streams/InputStream.h"

namespace cli {

class FileInputStream : public InputStream {
public:

    explicit FileInputStream(const std::string& filename);

    bool getChar(char& out) override;
    bool eof() const override;

private:
    std::ifstream file_;
    std::string filename_;
};

} // namespace cli

#endif // CLI_FILE_INPUT_STREAM_H

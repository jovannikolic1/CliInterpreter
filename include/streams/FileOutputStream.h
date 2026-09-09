#ifndef CLI_FILE_OUTPUT_STREAM_H
#define CLI_FILE_OUTPUT_STREAM_H

#include <fstream>
#include <string>

#include "streams/OutputStream.h"

namespace cli {

class FileOutputStream : public OutputStream {
public:
    FileOutputStream(const std::string& filename, bool append);

    void putChar(char c) override;

private:
    std::ofstream file_;
    std::string filename_;
};

} // namespace cli

#endif // CLI_FILE_OUTPUT_STREAM_H

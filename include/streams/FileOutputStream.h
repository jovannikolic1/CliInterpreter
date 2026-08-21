#ifndef CLI_FILE_OUTPUT_STREAM_H
#define CLI_FILE_OUTPUT_STREAM_H

#include <fstream>
#include <string>

#include "streams/OutputStream.h"

namespace cli {

// Output stream that writes into a text file, either truncating any
// previous content ('>' redirection) or appending to it ('>>' redirection).
class FileOutputStream : public OutputStream {
public:
    // Throws cli::FileSystemError if the file cannot be opened for writing.
    FileOutputStream(const std::string& filename, bool append);

    void putChar(char c) override;

private:
    std::ofstream file_;
    std::string filename_;
};

} // namespace cli

#endif // CLI_FILE_OUTPUT_STREAM_H

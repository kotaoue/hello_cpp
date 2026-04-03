#include "file_io.h"

#include <fstream>
#include <sstream>

bool write_text_file(const std::string& path, const std::string& content)
{
    std::ofstream ofs(path);
    if (!ofs) {
        return false;
    }
    ofs << content;
    return ofs.good();
}

bool read_text_file(const std::string& path, std::string& content)
{
    std::ifstream ifs(path);
    if (!ifs) {
        return false;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    content = oss.str();
    return ifs.good() || ifs.eof();
}

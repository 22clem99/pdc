#ifndef ZIP_READER_H
#define ZIP_READER_H

#include <string>
#include <vector>
#include <filesystem>

#include <miniz/miniz.h>

class ZipReader
{
public:
    static ZipReader open(const std::filesystem::path& path);

    std::vector<char> read_file(const std::string& filename);

    std::vector<std::string> list_files();

    std::string read_test_file(const std::string& filename);

    std::vector<uint8_t> read_binary_file(const std::string& filename);

    bool has_file(const std::string& filename);

    ~ZipReader();


private:
    ZipReader() = default;

    mz_zip_archive archive {};
    bool opened = false;
};



#endif
#ifndef ZIP_READER_H
#define ZIP_READER_H

#include <string>
#include <vector>
#include <filesystem>

#include <miniz/miniz.h>

enum class ZipReaderReturnStatus {
    OK,
    UNABLE_TO_OPEN_ARCHIVE,
    UNABLE_TO_FIND_FILE_IN_ARCHIVE,
    UNABLE_TO_READ_FILE_IN_ARCHIVE
};

class ZipReader
{
public:
    static ZipReader open(const std::filesystem::path& path);

    std::vector<char> read_file(const std::string& filename);

    std::vector<std::string> list_files();

    std::string read_test_file(const std::string& filename);

    std::vector<uint8_t> read_binary_file(const std::string& filename);

    bool has_file(const std::string& filename);

    ZipReaderReturnStatus get_return_status(void);

    ~ZipReader();


private:
    ZipReader() = default;

    mz_zip_archive archive {};
    bool opened = false;
    ZipReaderReturnStatus status;
};



#endif
#ifndef ZIP_READER_H
#define ZIP_READER_H

#include <string>
#include <vector>
#include <filesystem>

#include <miniz/miniz.h>
#include <utils/Image.hpp>

enum class ZipReaderReturnStatus {
    Ok,
    UnableToOpenArchive,
    UnableToFindFileInArchive,
    UnableToReadFileInArchive
};

class ZipReader
{
public:
    /**
     * @brief Open a ZIP archive
     *
     * @param path path of the archive to open
     * @return ZipReader
     */
    static ZipReader open(const std::filesystem::path& path);

    std::vector<char> read_file(const std::string& filename);

    std::vector<std::string> list_files();

    std::string read_text_file(const std::string& filename);

    std::vector<uint8_t> read_binary_file(const std::string& filename);

    bool has_file(const std::string& filename);

    bool find_file_with_unknown_extension(const std::string& base_name);

    ZipReaderReturnStatus get_return_status(void);

    ImgExtensions get_extension_status(void);

    ~ZipReader();


private:
    ZipReader() = default;

    mz_zip_archive archive {};
    bool opened = false;
    ZipReaderReturnStatus status;
    ImgExtensions ext_status;
};



#endif
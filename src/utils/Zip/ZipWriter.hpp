#ifndef ZIP_WRITER_H
#define ZIP_WRITER_H

#include <string>
#include <vector>
#include <filesystem>

#include <miniz/miniz.h>

enum class ZipWriterReturnStatus {
    Ok,
    UnableToCreateFile,
    UnableToAddFile,
    UnableToWriteInFile
};

class ZipWriter
{
public:
    static ZipWriter create(const std::filesystem::path& path);

    void add_file(const std::string& filename, const std::vector<char>& data);

    void add_string(const std::string& filename, const std::string& content);

    ZipWriterReturnStatus get_return_status(void);

    ~ZipWriter();

private:
    ZipWriter() = default;

    mz_zip_archive archive {};
    bool opened = false;
    ZipWriterReturnStatus status;
};


#endif
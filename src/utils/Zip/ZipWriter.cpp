#include <stdexcept>
#include <cstring>

#include "ZipWriter.hpp"


ZipWriter ZipWriter::create(const std::filesystem::path& path)
{
    ZipWriter writer;

    std::memset(&writer.archive, 0, sizeof(writer.archive));

    if (!mz_zip_writer_init_file(&writer.archive, path.string().c_str(), 0))
    {
        throw std::runtime_error("Failed to create zip archive: " + path.string());
    }

    writer.opened = true;

    return writer;
}

void ZipWriter::add_file(const std::string& filename,
                         const std::vector<char>& data)
{
    if (!mz_zip_writer_add_mem(
            &archive,
            filename.c_str(),
            data.data(),
            data.size(),
            MZ_BEST_COMPRESSION))
    {
        throw std::runtime_error("Failed to add file to archive: " + filename);
    }
}

void ZipWriter::add_string(const std::string& filename,
                           const std::string& content)
{
    if (!mz_zip_writer_add_mem(
            &archive,
            filename.c_str(),
            content.data(),
            content.size(),
            MZ_BEST_COMPRESSION))
    {
        throw std::runtime_error("Failed to add string to archive: " + filename);
    }
}

ZipWriter::~ZipWriter()
{
    if (opened)
    {
        mz_zip_writer_finalize_archive(&archive);
        mz_zip_writer_end(&archive);
    }
}
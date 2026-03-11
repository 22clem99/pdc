#include <stdexcept>
#include <cstring>
#include <optional>

#include "ZipReader.hpp"
#include <utils/Log.hpp>

ZipReader ZipReader::open(const std::filesystem::path& path)
{
    ZipReader reader;

    std::memset(&reader.archive, 0, sizeof(reader.archive));

    if (!mz_zip_reader_init_file(&reader.archive, path.string().c_str(), 0))
    {
        reader.status = ZipReaderReturnStatus::UnableToOpenArchive;
    }

    reader.opened = true;
    reader.status = ZipReaderReturnStatus::Ok;

    return reader;
}

std::vector<char> ZipReader::read_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
    {
        status = ZipReaderReturnStatus::UnableToFindFileInArchive;
    }

    std::vector<char> buffer(size);
    std::memcpy(buffer.data(), data, size);

    mz_free(data);
    status = ZipReaderReturnStatus::Ok;

    return buffer;
}

std::vector<std::string> ZipReader::list_files()
{
    std::vector<std::string> files;

    mz_uint num_files = mz_zip_reader_get_num_files(&archive);

    for (mz_uint i = 0; i < num_files; ++i)
    {
        mz_zip_archive_file_stat stat;

        if (mz_zip_reader_file_stat(&archive, i, &stat))
        {
            files.emplace_back(stat.m_filename);
        }
    }

    return files;
}

std::string ZipReader::read_text_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
    {
        status = ZipReaderReturnStatus::UnableToReadFileInArchive;
    }

    std::string result(static_cast<char*>(data), size);

    mz_free(data);
    status = ZipReaderReturnStatus::Ok;

    return result;
}

std::vector<uint8_t> ZipReader::read_binary_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
    {
        status = ZipReaderReturnStatus::UnableToReadFileInArchive;
    }

    std::vector<uint8_t> result(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);

    mz_free(data);
    status = ZipReaderReturnStatus::Ok;

    return result;
}

bool ZipReader::has_file(const std::string& filename)
{
    return mz_zip_reader_locate_file(&archive, filename.c_str(), nullptr, 0) != -1;
}

bool ZipReader::find_file_with_unknown_extension(const std::string& base_name)
{
    mz_uint num_files = mz_zip_reader_get_num_files(&archive);

    for (mz_uint i = 0; i < num_files; ++i)
    {
        mz_zip_archive_file_stat stat;

        if (!mz_zip_reader_file_stat(&archive, i, &stat))
            continue;

        std::string filename = stat.m_filename;

        std::filesystem::path p(filename);

        // check name
        if (p.replace_extension("").string() != base_name)
        {
            continue;
        }

        std::string ext = std::filesystem::path(filename).extension().string();

        ext_status = ImageExtension::string_to_extension(ext);

        if(ext_status != ImgExtensions::Unknown)
        {
            return true;
        }
    }
    return false;
}

ZipReaderReturnStatus ZipReader::get_return_status(void)
{
    return status;
}

ImgExtensions ZipReader::get_extension_status(void)
{
    return ext_status;
}

ZipReader::~ZipReader()
{
    if (opened)
    {
        mz_zip_reader_end(&archive);
    }
}
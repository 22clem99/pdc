#include <stdexcept>
#include <cstring>

#include "ZipReader.hpp"

ZipReader ZipReader::open(const std::filesystem::path& path)
{
    ZipReader reader;

    std::memset(&reader.archive, 0, sizeof(reader.archive));

    if (!mz_zip_reader_init_file(&reader.archive, path.string().c_str(), 0))
    {
        throw std::runtime_error("Failed to open zip archive: " + path.string());
    }

    reader.opened = true;

    return reader;
}

std::vector<char> ZipReader::read_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
    {
        throw std::runtime_error("File not found in archive: " + filename);
    }

    std::vector<char> buffer(size);
    std::memcpy(buffer.data(), data, size);

    mz_free(data);

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

std::string ZipReader::read_test_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
    {
        throw std::runtime_error("Cannot read file from archive: " + filename);
    }

    std::string result(static_cast<char*>(data), size);

    mz_free(data);

    return result;
}

std::vector<uint8_t> ZipReader::read_binary_file(const std::string& filename)
{
    size_t size = 0;

    void* data = mz_zip_reader_extract_file_to_heap(&archive, filename.c_str(), &size, 0);

    if (!data)
        throw std::runtime_error("Cannot read file from archive: " + filename);

    std::vector<uint8_t> result(static_cast<uint8_t*>(data), static_cast<uint8_t*>(data) + size);

    mz_free(data);

    return result;
}

bool ZipReader::has_file(const std::string& filename)
{
    return mz_zip_reader_locate_file(&archive, filename.c_str(), nullptr, 0) != -1;
}

ZipReader::~ZipReader()
{
    if (opened)
    {
        mz_zip_reader_end(&archive);
    }
}
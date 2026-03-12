/**
 * @file Image.cpp
 * @brief
 */
#include "Image.hpp"
#include <utils/Tab.hpp>
#include <utils/Log.hpp>


Image::Image(const std::filesystem::path& path)
{
    Log::debug("Trying to open the image:" + path.string());
    data = cv::imread(path.string(), cv::IMREAD_UNCHANGED);

    extension = ImageExtension::string_to_extension(path.extension().string());

    Log::debug("Mat type: " + std::to_string(data.type()) + " channels: " + std::to_string(data.channels()) + " depth: " + std::to_string(data.depth()));

    if (data.empty())
    {
        status = ImgStatus::ImgReadError;
    }
    status = ImgStatus::ImgReadSuccessfully;
}

Image::Image(const std::vector<uchar> image, ImgExtensions ext)
{
    Log::debug("Open a " + ImageExtension::extension_to_string(ext) + ", image size: " + std::to_string(image.size()));
    data = cv::imdecode(image, cv::IMREAD_UNCHANGED);

    extension = ext;

    Log::debug("Mat type: " + std::to_string(data.type()) + " channels: " + std::to_string(data.channels()) + " depth: " + std::to_string(data.depth()));

    if (data.empty())
    {
        status = ImgStatus::ImgReadError;
    }
    status = ImgStatus::ImgReadSuccessfully;
}

QImage Image::to_QImage(void) const
{
    return mat_to_QImage(data);
}

std::string Image::class_name(void)
{
    return "Image";
}

std::string Image::get_str(void) const
{
    return get_str(0);
}

std::string Image::get_str(const unsigned int tab) const
{
    return Tab::tab(tab) + "Image, value=TODO";
}

std::optional<std::string> Image::get_extension(void)
{
    if (!extension)
    {
        return "";
    }

    return ImageExtension::extension_to_string(extension.value());
}

std::vector<char> Image::encode_img(void)
{
    std::vector<uchar> buffer;

    if (!extension)
    {
        encode_status = ImgEncodeStatus::ImgEncodeErrorNoExtension;
        return std::vector<char>();
    }

    if (!cv::imencode(ImageExtension::extension_to_string(extension.value()), data, buffer))
    {
        encode_status = ImgEncodeStatus::ImgEncodeError;
        return std::vector<char>();
    }

    encode_status = ImgEncodeStatus::ImgEncodeSuccessfully;

    return std::vector<char>(buffer.begin(), buffer.end());
}

ImgStatus Image::get_img_status(void)
{
    return status;
}

ImgEncodeStatus Image::get_encode_status(void)
{
    return encode_status;
}
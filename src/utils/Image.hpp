/**
 * @file Image.hpp
 * @brief This file provide an Image abstraction class
 *
 * This image class will be helpfull for effective implementation
 * independantly of the graphical librairy chose
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <optional>

#include <utils/Qt/ImageUtils.hpp>
#include <utils/Log.hpp>

enum class ImgStatus {
    ImgReadSuccessfully,
    ImgReadError
};

enum class ImgEncodeStatus {
    ImgEncodeSuccessfully,
    ImgEncodeErrorNoExtension,
    ImgEncodeError
};

enum class ImgExtensions {
    Bmp,
    Dib,
    Jpeg,
    Jp2,
    Png,
    Webp,
    Pbm,
    Pgm,
    Ppm,
    Pxm,
    Pnm,
    Pfm,
    Sr,
    Ras,
    Tiff,
    Tif,
    Exr,
    Hdr,
    Pic,
    Unknown
};

class ImageExtension {
public:
    static constexpr std::string extension_to_string(ImgExtensions ext)
    {
        switch(ext)
        {
            case ImgExtensions::Bmp: return ".bpm";
            case ImgExtensions::Dib: return ".dib";
            case ImgExtensions::Jpeg: return ".jpeg";
            case ImgExtensions::Jp2: return ".jp2";
            case ImgExtensions::Png: return ".png";
            case ImgExtensions::Webp: return ".webp";
            case ImgExtensions::Pbm: return ".pbm";
            case ImgExtensions::Pgm: return ".pgm";
            case ImgExtensions::Ppm: return ".ppm";
            case ImgExtensions::Pxm: return ".pxm";
            case ImgExtensions::Pnm: return ".pnm";
            case ImgExtensions::Pfm: return ".pfm";
            case ImgExtensions::Sr: return ".sr";
            case ImgExtensions::Ras: return ".ras";
            case ImgExtensions::Tiff: return ".tiff";
            case ImgExtensions::Exr: return ".exr";
            case ImgExtensions::Hdr: return ".hdr";
            case ImgExtensions::Pic: return ".pic";
            default: return "";
        }
    }

    static ImgExtensions string_to_extension(const std::string& s)
    {
        std::string lower = s;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        Log::debug("lower " + lower);

        if (lower == ".bpm") return ImgExtensions::Bmp;
        if (lower == ".dib") return ImgExtensions::Dib;
        if (lower == ".jpeg"|| lower == ".jpeg" || lower == "jpe") return ImgExtensions::Jpeg;
        if (lower == ".jp2") return ImgExtensions::Jp2;
        if (lower == ".png") return ImgExtensions::Png;
        if (lower == ".webp") return ImgExtensions::Webp;
        if (lower == ".pbm") return ImgExtensions::Pbm;
        if (lower == ".pgm") return ImgExtensions::Pgm;
        if (lower == ".ppm") return ImgExtensions::Ppm;
        if (lower == ".pxm") return ImgExtensions::Pxm;
        if (lower == ".pnm") return ImgExtensions::Pnm;
        if (lower == ".pfm") return ImgExtensions::Pfm;
        if (lower == ".sr") return ImgExtensions::Sr;
        if (lower == ".ras") return ImgExtensions::Ras;
        if (lower == ".tiff" || lower == ".tif") return ImgExtensions::Tiff;
        if (lower == ".exr") return ImgExtensions::Exr;
        if (lower == ".hdr") return ImgExtensions::Hdr;
        if (lower == ".pic") return ImgExtensions::Pic;

        return ImgExtensions::Unknown;
    }
};


class Image {
public:
    cv::Mat data;
    Image() = default;
    Image(const std::filesystem::path& path);
    Image(const std::vector<uchar> image, ImgExtensions ext);

    QImage to_QImage(void) const;

    // static bool equal(Image a, Image b);
    // static bool greater(Image a, Image b);
    // static bool lesser(Image a, Image b);
    // static bool equal_and_greater(Image a, Image b);
    // static bool equal_and_lesser(Image a, Image b);
    // static bool is_divisible(Image a, Image div);
    static std::string class_name(void);
    std::string get_str(void) const;
    std::string get_str(const unsigned int tab) const;
    std::optional<std::string> get_extension(void);
    std::vector<char> encode_img(void);
    ImgStatus get_img_status(void);
    ImgEncodeStatus get_encode_status(void);

private:
    ImgStatus status;
    ImgEncodeStatus encode_status;
    std::optional<ImgExtensions> extension;
};

#endif
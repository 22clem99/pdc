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

enum class ImgStatus {
    ImgReadSuccessfully,
    ImgReadError
};

enum class ImgEncodeStatus {
    ImgEncodeSuccessfully,
    ImgEncodeErrorNoExtension,
    ImgEncodeError
};

class Image {
public:
    cv::Mat data;
    Image() = default;
    Image(const std::filesystem::path& path);

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
    std::optional<std::string> extension;
};

#endif
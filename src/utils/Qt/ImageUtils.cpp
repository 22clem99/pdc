#include "ImageUtils.hpp"
#include <utils/Log.hpp>

QImage mat_to_QImage(const cv::Mat& mat)
{
    Log::debug("Mat type: " + std::to_string(mat.type()) + " channels: " + std::to_string(mat.channels()) + " depth: " + std::to_string(mat.depth()));

    if (mat.empty())
        return QImage();

    cv::Mat img;

    // Convert to 8-bit if needed
    if (mat.depth() != CV_8U)
    {
        double min, max;
        cv::minMaxLoc(mat, &min, &max);

        if (max - min < 1e-6)
            max = min + 1.0;

        mat.convertTo(img, CV_8U, 255.0 / (max - min), -min * 255.0 / (max - min));
    }
    else
    {
        img = mat;
    }

    switch (img.channels())
    {
        case 1:
            return QImage(
                img.data,
                img.cols,
                img.rows,
                img.step,
                QImage::Format_Grayscale8
            ).copy();

        case 3:
        {
            cv::Mat rgb;
            cv::cvtColor(img, rgb, cv::COLOR_BGR2RGB);

            return QImage(
                rgb.data,
                rgb.cols,
                rgb.rows,
                rgb.step,
                QImage::Format_RGB888
            ).copy();
        }

        case 4:
            return QImage(
                img.data,
                img.cols,
                img.rows,
                img.step,
                QImage::Format_ARGB32
            ).copy();

        default:
            break;
    }

    return QImage();
}
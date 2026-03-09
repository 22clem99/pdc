#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <QImage>
#include <opencv2/opencv.hpp>

QImage mat_to_QImage(const cv::Mat& mat);

#endif
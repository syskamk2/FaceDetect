#ifndef MY_IMG_PROC_H
#define MY_IMG_PROC_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ResultSet.h"

int preproc(cv::VideoCapture cap, ResultSet* result);
int makeDiff(ResultSet* result);
size_t countMat(const cv::Mat& mat);
int contour(cv::Mat& diff);

#endif
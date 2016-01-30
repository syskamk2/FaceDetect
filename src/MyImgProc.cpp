#include "MyImgProc.h"
#include "CommonConfig.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string.h>

int preproc(cv::VideoCapture cap, ResultSet* result)
{
  cap >> result->frame;  // キャプチャ
  result->gray = cv::Mat(result->frame.rows, result->frame.cols, CV_8UC1);
  cv::cvtColor(result->frame, result->gray, CV_RGB2GRAY);
  result->diff = cv::Mat(result->gray.rows, result->gray.cols, CV_8UC1);
  result->diff = cv::Scalar::all(0);

  return 0;
}

int makeDiff(ResultSet* result)
{

  cv::absdiff(result->gray, result->prev, result->diff);
  cv::threshold(result->diff, result->diff, THRESH, UCHAR_MAX, CV_THRESH_BINARY);

  for (int i = 0; i < MORPHNUM; ++i)
  {
    cv::dilate(result->diff, result->diff, cv::Mat());
    cv::erode(result->diff, result->diff, cv::Mat());
  }

  return 0;
}

size_t countMat(const cv::Mat mat)
{
  size_t pix = 0;
  const int w = mat.cols;
  const int h = mat.rows;

  for (int y = 0; y < h; ++y)
  {
    for (int x = 0; x < w; ++x)
    {
      if (mat.data[y * mat.step + x * mat.elemSize()] > 0)
      {
        pix++;
      }
    }
  }

  return pix;
}

//輪郭抽出
int contour(cv::Mat& diff)
{
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;

  cv::findContours(diff, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  cv::Mat contourimg = cv::Mat(diff.rows, diff.cols, CV_8UC1);
  contourimg = cv::Scalar::all(0);
  const int idx = -1;
  cv::drawContours(contourimg, contours, idx, cv::Scalar(UCHAR_MAX), 2);

  imshow("Contour", contourimg);
  return 0;
}
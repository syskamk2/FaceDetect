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
  for (int i = 0; i < BOUND_RECTNUM; ++i)
  {
    result->boundrect[i] = cv::Rect();
  }
  return 0;
}

static int maxavemat(const cv::Mat& mat, ResultSet* result)
{
  long long int ave = 0;
  int max = INT_MIN;
  int pix;
  const int w = mat.cols;
  const int h = mat.rows;

  for (int y = 0; y < h; ++y)
  {
    for (int x = 0; x < w; ++x)
    {
      pix = mat.data[y * mat.step + x * mat.elemSize()];
      if (pix > max)
      {
        max = pix;
      }
      ave += pix;
    }
  }
  ave /= (w * h);
  result->diff_ave = static_cast<int>(ave);
  result->diff_max = max;
  return 0;
}

int makeDiff(ResultSet* result)
{
  cv::absdiff(result->gray, result->prev, result->diff);
  maxavemat(result->diff, result);
  //cv::threshold(result->diff, result->diff, THRESH, UCHAR_MAX, CV_THRESH_BINARY);

  const int th1 = MIN(CANNY_TH1, CANNY_TH2);
  const int th2 = MAX(CANNY_TH1, CANNY_TH2);
  cv::Canny(result->diff, result->diff, th1, th2);

  for (int i = 0; i < MORPHNUM; ++i)
  {
    cv::dilate(result->diff, result->diff, cv::Mat());
    cv::erode(result->diff, result->diff, cv::Mat());
  }

  return 0;
}

size_t countMat(const cv::Mat& mat)
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
int boundFace(ResultSet* result)
{
  cv::vector<cv::vector<cv::Point> > contours;
  cv::vector<cv::Vec4i> hierarchy;
  
  cv::findContours(result->diff, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
  
  cv::vector<cv::vector<cv::Point> > contourpoly(contours.size());

  for (int i = 0; i < contours.size(); ++i)
  {
    if (i >= BOUND_RECTNUM)
    {
      break;
    }
    cv::approxPolyDP(cv::Mat(contours[i]), contourpoly[i], 3, true);
    result->boundrect[i] = cv::boundingRect(contourpoly[i]);
  }

  return 0;
}
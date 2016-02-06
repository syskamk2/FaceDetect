#ifndef RESULTSET_H
#define RESULTSET_H

#include "CommonConfig.h"
#include <iostream>
#include <opencv2/core/core.hpp>

typedef struct ResultSet
{
  int serial;
  size_t nPix;//差分画像の画素数

  int diff_max;//差分最大値
  int diff_ave;//差分平均値

  cv::Mat frame; //入力画像
  cv::Mat gray;//入力画像グレースケール
  cv::Mat diff;//2フレーム間の差分画像

  cv::Mat prev;//1フレーム前のdiff

  cv::Rect boundrect[BOUND_RECTNUM];
  
  ResultSet();
} ResultSet;

int writelog(FILE *log, ResultSet* result);
int writeilog(ResultSet* result);
int showlog(ResultSet* result);
#endif
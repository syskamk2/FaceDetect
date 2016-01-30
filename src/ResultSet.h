#ifndef RESULTSET_H
#define RESULTSET_H

#include<iostream>
#include <opencv2/core/core.hpp>

typedef struct ResultSet
{
  int serial;
  size_t nPix;//·•ª‰æ‘œ‚Ì‰æ‘f”

  int diff_max;//·•ªÅ‘å’l
  int diff_ave;//·•ª•½‹Ï’l

  cv::Mat frame;
  cv::Mat gray;
  cv::Mat diff;

  cv::Mat prev;
  
  ResultSet();
} ResultSet;

int writelog(FILE *log, ResultSet* result);
int writeilog(ResultSet* result);
int showlog(ResultSet* result);
#endif
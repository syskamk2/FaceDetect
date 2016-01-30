#ifndef RESULTSET_H
#define RESULTSET_H

#include<iostream>
#include <opencv2/core/core.hpp>

typedef struct ResultSet
{
  int serial;
  size_t nPix;

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
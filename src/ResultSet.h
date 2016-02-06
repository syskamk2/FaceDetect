#ifndef RESULTSET_H
#define RESULTSET_H

#include "CommonConfig.h"
#include <iostream>
#include <opencv2/core/core.hpp>

typedef struct ResultSet
{
  int serial;
  size_t nPix;//�����摜�̉�f��

  int diff_max;//�����ő�l
  int diff_ave;//�������ϒl

  cv::Mat frame; //���͉摜
  cv::Mat gray;//���͉摜�O���[�X�P�[��
  cv::Mat diff;//2�t���[���Ԃ̍����摜

  cv::Mat prev;//1�t���[���O��diff

  cv::Rect boundrect[BOUND_RECTNUM];
  
  ResultSet();
} ResultSet;

int writelog(FILE *log, ResultSet* result);
int writeilog(ResultSet* result);
int showlog(ResultSet* result);
#endif
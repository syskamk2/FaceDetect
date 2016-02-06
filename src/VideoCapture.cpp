#include "ResultSet.h"
#include "CommonConfig.h"
#include "MyImgProc.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string.h>
#include <Windows.h>
#include <iostream>

int main(int argc, char *argv[])
{
  cv::VideoCapture cap(0);
  // �ݒ肵�Ă����f����Ă��Ȃ����������璍��
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 240);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 160);
  // �J�������I�[�v���ł������̊m�F
  if (!cap.isOpened())
  {
    return -1;
  }

  cv::namedWindow("Capture", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
  cv::namedWindow("Diff", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

  ResultSet* result = new ResultSet();

  FILE * mylog;
  char logf[BSIZE];
  sprintf_s<BSIZE>(logf, DATA_DIR LOGFILE);
  fopen_s(&mylog, logf, "w");
  
  while (1) {
    preproc(cap, result);
    //�f�������肵�Ă��珈���J�n
    if (result->serial > START_FRAME)
    {
      makeDiff(result);
      result->nPix = countMat(result->diff);
      boundFace(result);
    }

    result->serial++;
    result->prev = result->gray.clone();
    //output log
    writelog(mylog, result);
    writeilog(result);
    showlog(result);

    if (result->serial > MAX_FRAME)
    {
      break;
    }
    Sleep(waitmil - WAITKEYMIL);
  }

  if (mylog != NULL)
  {
    fclose(mylog);
  }
  if (result != NULL)
  {
    delete result;
  }
  return 0;
}
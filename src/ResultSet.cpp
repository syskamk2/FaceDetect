#include "ResultSet.h"
#include "CommonConfig.h"
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

ResultSet::ResultSet() :
nPix(0),
serial(0),
diff_ave(0),
diff_max(0)
{
  frame = cv::Mat();
  diff = cv::Mat();
  gray = cv::Mat();
  prev = cv::Mat();
}

int writelog(FILE* file, ResultSet* result)
{
  if (file == NULL)
  {
    return 1;
  }
  char log[BSIZE];
  sprintf_s<BSIZE>(log, "%d, %d,", result->serial, result->nPix);
  fprintf_s(file, log);
  sprintf_s<BSIZE>(log, " %d, %d", result->diff_max, result->diff_ave);
  fprintf_s(file, log);
  sprintf_s<BSIZE>(log, "\n");
  fprintf_s(file, log);
  return 0;
}

int writeilog(ResultSet* result)
{
  char fname[BSIZE];

  //“ü—Í‰æ‘œ
  sprintf_s<BSIZE>(fname, DATA_DIR "\\img%03d.png", result->serial);
  cv::imwrite(fname, result->gray);
  
  sprintf_s<BSIZE>(fname, DATA_DIR "\\diff%03d.png", result->serial);
  cv::imwrite(fname, result->diff);

  return 0;
}
int showlog(ResultSet* result)
{
  cv::imshow("Capture", result->gray);
  cv::imshow("Diff", result->diff);

  cv::waitKey(WAITKEYMIL);
  return 0;
}
#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include<Windows.h>

#define DATA_DIR "C:\\Users\\Public\\Study\\PicData"
#define DATA_ID "001"
#define FPS (10)
#define THRESH (17)
#define BSIZE (4096)
#define WAITKEYMIL (10)
#define LOGFILE "\\log.csv"
#define MAX_FRAME (80)
#define MORPHNUM (1)
#define START_FRAME (5)
#define CANNY_TH1 (25)
#define CANNY_TH2 (90)
#define BOUND_RECTNUM (4)

const DWORD waitmil = (1000 / FPS);

#endif
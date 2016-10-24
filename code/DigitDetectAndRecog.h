#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"
#include "cxcore.h"
#include "cv.h"
#include "highgui.h"

#include <io.h>
#include "direct.h"  

using namespace std;
using namespace cv;

void videoCapture();
void   visit(string path,int layer);//文件夹遍历函数 
void digitSegment(Mat img_s);// 图像块分割
#include "DigitDetectAndRecog.h"

// 文件夹遍历函数
void   visit(string path,int layer)     
{     
	struct _finddata_t   filefind;     
	string  curr=path+"*.*";     
	int   done=0,i,handle;     
	if((handle=_findfirst(curr.c_str(),&filefind))==-1)
		return;  
	while(!(done=_findnext(handle,&filefind)))     
	{         
		printf("%s\n",filefind.name);      
		if(!strcmp(filefind.name,".."))
		{  
			continue;  
		}  
		for(i=0;i<layer;i++)
		{
			cout<<"     ";
		}
		if((_A_SUBDIR==filefind.attrib)) //是目录  
		{             
			continue;     
		}     
		else//不是目录，是文件       
		{    // 操作写在这里
			VideoCapture cap(path+filefind.name);
			if(!cap.isOpened())
			{
				cout<< "opening video"<<filefind.name<<" failed,exit";
				return;
			}
			namedWindow("Frame",CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
			Mat frame;
			while(1)
			{
				cap>>frame;
				imshow("Frame",frame);
				vector<Mat> channels;
				split(frame,channels);
				Mat img_B=channels[0];
				Mat img_G=channels[1];
				Mat img_R=channels[2];
				
				digitSegment(img_R);

				waitKey(500);
			}
		}     
	}             
	_findclose(handle);       
}

void digitSegment(Mat img_s)
{
	int thresh=240;//二值化阈值
	int K=7; //对原图切分的比例
	int rows=img_s.rows;
	int cols=img_s.cols;
	Mat img_d=Mat(rows,cols,CV_8UC1);
	img_d=img_s.clone();

	for(int row=0;row<rows;row++)
		for(int col=0;col<cols;col++)
		{
			if(img_s.at<uchar>(row,col)>thresh)
			{
				img_d.at<uchar>(row,col)=255;
			}
			else
			{
				img_d.at<uchar>(row,col)=0;
			}
		}
	Rect rect(floor(cols/K),floor(rows/K),floor(cols*(K-2)/K),floor(rows*(K-2)/K));
	Mat img_d2=img_d(rect);
	// 膨胀腐蚀

	return;
}
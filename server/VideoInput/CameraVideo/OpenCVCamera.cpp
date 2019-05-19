#include "OpenCVCamera.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/video.hpp>

using namespace std;
using namespace cv;
VideoCapture cap;

Mat mFrame;
Mat yuv_frame;

int CameraInit(YUVFrame * frame)
{
	namedWindow( "Camera",WINDOW_AUTOSIZE);
	frame->width = 640;
	frame->height = 480;
	cap.open(0);
	if(!cap.isOpened())  
	{  
		return -1;
	}
	return 0;
}

int CameraGetPicture(YUVFrame * frame)
{
	cap>>mFrame;
	cvtColor(mFrame, yuv_frame, CV_BGR2YUV_I420);
	frame->data = yuv_frame.data;
	imshow("Camera",mFrame);
	waitKey(1);
	return 0;
}

int CameraRelease()
{
	cap.release();
	destroyWindow("Camera");
}



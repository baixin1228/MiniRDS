#include "VideoInput.h"
#include "OpenCVCamera.h"

VideoInputOps video_input_ops = 
{
	CameraInit,
	CameraGetPicture,
	CameraRelease
};


int VideoInputInit(YUVFrame *frame)
{
	video_input_ops.Init(frame);
}

int GetYUV422Picture(YUVFrame *frame)
{
	video_input_ops.GetPicture(frame);
}
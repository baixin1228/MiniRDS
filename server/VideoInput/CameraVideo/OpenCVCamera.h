
#ifndef _OPENCV_CAMERA_H
#define _OPENCV_CAMERA_H
#include "VideoInput.h"


#ifdef __cplusplus
extern "C"
{
#endif

int CameraInit(YUVFrame *frame);
int CameraGetPicture(YUVFrame *frame);
int CameraRelease();

#ifdef __cplusplus
}
#endif

#endif
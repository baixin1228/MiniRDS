#ifndef _VIDEO_INPUT_H
#define _VIDEO_INPUT_H
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <stdint.h>

AVFrame *frame;

typedef struct
{
	uint8_t * data;
	int width;
	int height;
}YUVFrame;


typedef struct 
{
	int (*Init)(YUVFrame *frame);
	int (*GetPicture)(YUVFrame *frame);
	int (*Release)();
}VideoInputOps;

int VideoInputInit(YUVFrame *frame);
int GetYUV422Picture(YUVFrame *frame);


#endif
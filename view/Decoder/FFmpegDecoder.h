
#ifndef FFMPEG_DECODER_H_
#define FFMPEG_DECODER_H_


#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
    
#ifdef __cplusplus
};
#endif

int FFmpegDecoderInit();
int FFmpegDecoderGetYUVData(char * input_data,int size,char * output_data);

#endif

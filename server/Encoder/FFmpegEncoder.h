#ifndef _FFMPEG_ENCODER_H
#define _FFMPEG_ENCODER_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#ifdef __cplusplus
};
#endif

int FFmpegEncoderInit();
int GetFFmpegEncodeData(uint8_t *yuv_frame,uint8_t ** output_data);

#endif

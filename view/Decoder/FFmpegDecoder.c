#include "FFmpegDecoder.h"
#include <stdint.h>

AVFrame *frame;
AVPacket pkt;
AVCodec *codec;
AVCodecContext *coder_contxt;

int FFmpegDecoderInit()
{
    avcodec_register_all();
    
    int fromat = AV_PIX_FMT_YUV420P;
	codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (!codec) {
		printf("Codec not found\n");
		return -1;
	}
	coder_contxt = avcodec_alloc_context3(codec);
	
	coder_contxt->width = 640;
	coder_contxt->height = 480;
    
	coder_contxt->delay = 0;
	coder_contxt->pix_fmt = fromat;


	av_opt_set(coder_contxt->priv_data, "preset", "superfast", 0);
	av_opt_set(coder_contxt->priv_data, "tune", "zerolatency", 0);
    if(codec->capabilities&CODEC_CAP_TRUNCATED)
            coder_contxt->flags|= CODEC_FLAG_TRUNCATED;
	int re = avcodec_open2(coder_contxt, codec, NULL);

	if (re < 0) {
		printf("Could not open codec:%d\n",fromat);
		return -1;
	}

	frame = av_frame_alloc();
	if (!frame) {

		printf("%s\n","Could not allocate video frame\n");
		return -1;
	}
	frame->format = AV_PIX_FMT_YUV420P;
	frame->width  = 640;
	frame->height = 480;
    
	av_init_packet(&pkt);

}

int FFmpegDecoderGetYUVData(char * input_data,int size,char * output_data)
{
    int len, got_frame;
    
    av_free_packet(&pkt);
    
    pkt.size = size;
    pkt.data = input_data;

    len = avcodec_decode_video2(coder_contxt, frame, &got_frame, &pkt);
 
    if (got_frame)
    {
        int i;
        for(i = 0;i<640*480;i++)
        {
           output_data[i] = frame->data[0][i];
        }
        for(i = 0;i<640*480/4;i++)
        {
           output_data[i+640*480] = frame->data[1][i];
        }
        for(i = 0;i<640*480/4;i++)
        {
           output_data[i+640*480*5/4] = frame->data[2][i];
        }
        return len;
    }
    return -1;
}

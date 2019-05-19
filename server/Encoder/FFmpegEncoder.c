#include "FFmpegEncoder.h"


AVFrame *frame;
AVPacket pkt;
AVCodec *codec;
AVCodecContext *coder_contxt;

int i = 0;

int FFmpegEncoderInit()
{
	int fromat = AV_PIX_FMT_YUV420P;
	codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!codec) {
		printf("Codec not found\n");
		return -1;
	}
	coder_contxt = avcodec_alloc_context3(codec);
	
	coder_contxt->width = 640;
	coder_contxt->height = 480;

	coder_contxt->bit_rate = 400000;
	//coder_contxt->time_base = (AVRational){1,25};
	coder_contxt->gop_size = 120;
	//coder_contxt->b_frame_strategy = 1;
	coder_contxt->time_base.num=1;
	coder_contxt->time_base.den=25;
	//coder_contxt->max_b_frames = 0;
	coder_contxt->max_b_frames = 0;
	coder_contxt->delay = 0;
	coder_contxt->pix_fmt = fromat;


	av_opt_set(coder_contxt->priv_data, "preset", "superfast", 0);
	av_opt_set(coder_contxt->priv_data, "tune", "zerolatency", 0);

	int re = avcodec_open2(coder_contxt, codec, NULL);
	av_opt_set(coder_contxt->priv_data, "tune", "zerolatency", 0);
	if (re < 0) {
		printf("%s\n", "Could not open codec:%d\n");
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

	int ret = av_image_alloc(frame->data, frame->linesize, 640, 480, fromat, 32);
	if (ret < 0) {
		printf("Could not allocate raw picture buffer\n");
		return -1;
	}

	av_init_packet(&pkt);
	pkt.size = 1000000;
}	

int got_output;

int GetFFmpegEncodeData(uint8_t *yuv_frame,uint8_t ** output_data)
{
    i++;
    av_free_packet(&pkt);
    
	frame->data[0] = yuv_frame;
	frame->data[1] = yuv_frame+640*480;
	frame->data[2] = yuv_frame+640*480*5/4;

	frame->pts = i;
	// printf("3:%d\n", frame->data[0][0]);
	// printf("4:%d\n", yuv_frame->data[0]);
	
	int ret = avcodec_encode_video2(coder_contxt, &pkt, frame, &got_output);

	if (ret < 0)
	{
		printf("%s\n","Error encoding frame\n");
		return -1;
	}

	if (got_output)
	{
		int ss = pkt.size;
        if (pkt.flags & AV_PKT_FLAG_KEY) // is keyframe
        {
            printf("    key frame index:%d size:%d\n", i,ss);
        }else{
            printf("not key frame index:%d size:%d\n", i,ss);
        }
        *output_data = pkt.data;
        return pkt.size;
    }
    else{
        printf("mission frame!\n");
        return -1;
    }
}

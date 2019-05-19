#include "fbtool.c"
#include "VideoInput.h"
#include "FFmpegEncoder.h"
#include "SocketUdp.h"

int main()
{
	FBDEV fbdev;

	memset(&fbdev,0,sizeof(FBDEV));
	strcpy(fbdev.dev,"/dev/fb0");	

	if(0 == fb_open(&fbdev)){
		printf("Open fail!!\n");
		return -1;
	}
	
	//打印frame buffer 所占内存的开始地址　
	pmem_start(&fbdev);
	//打印FB_TYPE
	p_type(&fbdev);
	//打印可见清晰度
	p_visible_res(&fbdev);
	//打印虚拟分辨率
	p_virt_res(&fbdev);
	//打印虚拟到可见的偏移量
	p_offset(&fbdev);
	//打印每个像素的位数
	p_bpp(&fbdev);
	//打印R,G,B和透明度
	p_rgbt(&fbdev);
	//打印在内存中的高度和宽度
	p_hw(&fbdev); 

	fb_close(&fbdev);

	YUVFrame frame;
	if(VideoInputInit(&frame) == -1)
	{
		printf("%s\n", "Camera init error!");
		return -1;
	}
	if(FFmpegEncoderInit() == -1)
	{
		printf("%s\n", "FFmpeg init error!");
		return -1;
	}
    if(SocketUdpServerInit("0.0.0.0",3721) == -1)
    {
        printf("socket error\n");
        return -1;
    }
    
    char buffer[1000];
    struct sockaddr_in client_addr;
    SocketUdpServerReadData(buffer,sizeof(buffer),&client_addr);
    printf("%s\n",buffer);
    if(strcmp("rds_client_connect!\n",buffer) == 0)
    {
        printf("%s\n",buffer);
        uint8_t *encode_data;
        while(1)
        {
            GetYUV422Picture(&frame);
            int size =GetFFmpegEncodeData(frame.data,&encode_data);
            SocketUdpServerSendData(encode_data,size,&client_addr);
        }
    }
    sleep(10);
	return 0;
}

#include "main.h"
#include <string.h>
extern "C" {
#include "SocketUdp.h"
#include "FFmpegDecoder.h"
}
#include <unistd.h>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

int main()
{
    sleep(1);
    if(SocketUdpClientInit("127.0.0.1",3721) == -1)
    {
        printf("socket error\n");
        return -1;
    }
    char * start_cmd = "rds_client_connect!\n";
    SocketUdpClientSendData(start_cmd,strlen(start_cmd)+1);
    
    if(FFmpegDecoderInit() == -1)
    {
        printf("ffmpeg decoder init error\n");
        return -1;
    }
    
    char recv_buffer[1000000];
    char yuv_buffer[1000000];
    
    namedWindow( "Desktop",WINDOW_AUTOSIZE);
    Mat yuv_frame(720, 640,CV_8UC1);
    Mat rgb_frame;
    
    while(1)
    {
        int size = SocketUdpClientReceiveData(recv_buffer,1000000);
        int size2 = FFmpegDecoderGetYUVData(recv_buffer,size,yuv_buffer);
        if(size2 > 0){
        yuv_frame.data = (uchar *)yuv_buffer;
        printf("%d %d\n",yuv_frame.data[1000],size2);
        cvtColor(yuv_frame, rgb_frame, CV_YUV2BGR_I420);
        imshow("Desktop",rgb_frame);
        waitKey(1);
        }
    }
}

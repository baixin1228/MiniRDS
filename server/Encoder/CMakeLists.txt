include_directories(./)

aux_source_directory(./ encoder_list)

add_library(VideoEncoder STATIC ${encoder_list})

link_directories("/usr/local/ffmpeg/lib/")
LINK_LIBRARIES(/usr/local/ffmpeg/lib/)
target_link_libraries(VideoEncoder avformat.so)

target_link_libraries(VideoEncoder avcodec.so)
target_link_libraries(VideoEncoder avutil.so)

target_link_libraries(VideoEncoder m.so)

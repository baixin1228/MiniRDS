include_directories(./)


aux_source_directory(./ decoder_list)

add_library(FFmpegDecoder STATIC ${decoder_list})

link_directories(/usr/local/ffmpeg/lib)
target_link_libraries(FFmpegDecoder avformat.so)
target_link_libraries(FFmpegDecoder avcodec.so)
target_link_libraries(FFmpegDecoder avutil.so)
target_link_libraries(FFmpegDecoder swscale.so)

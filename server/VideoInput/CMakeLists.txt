include_directories(./ ./CameraVideo /usr/local/ffmpeg/include/)

add_subdirectory(CameraVideo)

aux_source_directory(./ video_input_list)

add_library(VideoInput STATIC ${video_input_list})

target_link_libraries(VideoInput OpenCVCamera)

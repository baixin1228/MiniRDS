#include_directories(./)

#aux_source_directory(./ encoder_list)

#add_library(VideoEncoder STATIC ${encoder_list})

add_subdirectory(Socket)

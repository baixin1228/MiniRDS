include_directories(./)

aux_source_directory(./ socket_list)

add_library(MiniSocket STATIC ${socket_list})

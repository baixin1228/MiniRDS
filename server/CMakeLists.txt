AUX_SOURCE_DIRECTORY(. SRC_LIST)
include_directories(./)
include_directories(./fbtool)
include_directories(./VideoInput)
include_directories(../common/Socket)
include_directories(./Encoder/)

add_subdirectory(fbtool)
add_subdirectory(VideoInput)
add_subdirectory(Encoder/)

ADD_EXECUTABLE(mini_rds_server ${SRC_LIST})

target_link_libraries(mini_rds_server fbtool)
target_link_libraries(mini_rds_server VideoInput)
target_link_libraries(mini_rds_server VideoEncoder)
target_link_libraries(mini_rds_server MiniSocket)

SET(EXECUTABLE_OUTPUT_PATH ../)

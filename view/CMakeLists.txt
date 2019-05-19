AUX_SOURCE_DIRECTORY(. SRC_LIST)
include_directories(./)
include_directories(../common/Socket)
include_directories(./Decoder/)

ADD_EXECUTABLE(mini_rds_view ${SRC_LIST})

add_subdirectory(Decoder/)

target_link_libraries(mini_rds_view MiniSocket)
target_link_libraries(mini_rds_view FFmpegDecoder)

FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(mini_rds_view ${OpenCV_LIBS})


SET(EXECUTABLE_OUTPUT_PATH ../)

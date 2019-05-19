include_directories(./)

aux_source_directory(./ opencv_list)

FIND_PACKAGE(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(OpenCVCamera STATIC ${opencv_list})
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(OpenCVCamera ${OpenCV_LIBS})
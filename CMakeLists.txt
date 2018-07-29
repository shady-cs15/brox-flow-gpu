cmake_minimum_required(VERSION 3.4)
PROJECT(project_brox)

FIND_PACKAGE( OpenCV 3 REQUIRED PATHS "/home/vroy/root" NO_DEFAULT_PATH )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")
MESSAGE("OpenCV library directories: ${OpenCV_LIB_DIR}")
MESSAGE("OpenCV include directories: ${OpenCV_INCLUDE_DIRS}")
MESSAGE("OpenCV link directories: ${OpenCV_LIBS}")

set (CMAKE_CXX_STANDARD 11)

set (INCLUDE utils)
set(SRC compute_flow.cpp 
        utils/minmax.cpp
        utils/flowutils.cpp)

include_directories(${OpenCV_INCLUDE_DIRS} ${INCLUDE})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE( compute_flow ${SRC})
TARGET_LINK_LIBRARIES( compute_flow ${OpenCV_LIBS} )

cmake_minimum_required(VERSION 3.3)

find_package(Caffe REQUIRED)
include_directories(${Caffe_INCLUDE_DIRS})
add_definitions(${Caffe_DEFINITIONS})    # ex. -DCPU_ONLY
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

option(CPU_ONLY "Use CPU only for Caffe" OFF)
option(USE_CUDNN "Use CuDNN library for Caffe" ON)

find_package(OpenCV REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.55.0 COMPONENTS filesystem)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/include)
include_directories(/home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/.build_release/src)
include_directories(${PROJECT_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(PROJECTNAME sar_dl)

add_executable(sar_dl main2.cpp)
target_link_libraries(${PROJECTNAME} /usr/lib/x86_64-linux-gnu/libglog.so)
target_link_libraries(${PROJECTNAME} /usr/lib/x86_64-linux-gnu/libboost_system.so)
target_link_libraries(${PROJECTNAME} ${OpenCV_LIBRARIES})
target_link_libraries(${PROJECTNAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECTNAME} /home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/build/lib/libcaffe.so)
target_link_libraries(${PROJECTNAME} /opt/intel/mkl/lib/intel64/libmkl_rt.so)
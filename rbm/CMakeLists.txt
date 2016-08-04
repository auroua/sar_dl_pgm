cmake_minimum_required(VERSION 3.3)

find_package(Caffe REQUIRED)
include_directories(${Caffe_INCLUDE_DIRS})
add_definitions(${Caffe_DEFINITIONS})    # ex. -DCPU_ONLY
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

option(CPU_ONLY "Use CPU only for Caffe" OFF)
option(USE_CUDNN "Use CuDNN library for Caffe" ON)

find_package(OpenCV REQUIRED)

include_directories("/home/aurora/hdd/workspace/ClionProjects2/sar_dl_pgm")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/include)
include_directories(/home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/.build_release/src)
include_directories(/usr/local/cuda/include)


SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(sar_rbm caffe_rbm.cpp)
target_link_libraries(sar_rbm ${OpenCV_LIBRARIES})
target_link_libraries(sar_rbm /home/aurora/hdd/workspace/ClionProjects2/caffe_new/caffe-master/build/lib/libcaffe.so)
#target_link_libraries(sar_rbm /opt/intel/mkl/lib/intel64/libmkl_rt.so)
target_link_libraries(sar_rbm /usr/local/cuda/lib64/libcublas.so)
target_link_libraries(sar_rbm /home/aurora/hdd/workspace/ClionProjects2/sar_dl_pgm/mshadow/tensor_cpu-inl.h)
target_link_libraries(sar_rbm /home/aurora/hdd/workspace/ClionProjects2/sar_dl_pgm/mshadow/expr_engine-inl.h)
cmake_minimum_required(VERSION 3.3)
project(sar_dl_pgm)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(PROJECTNAME sar_dl_pgm)

#set(CMAKE_MODULE_PATH ../sar_dl_pgm)
#add_subdirectory(deep_learning)
add_subdirectory(image_process)
add_subdirectory(rbm)
add_subdirectory(mshadow)
add_executable(sar_dl_pgm main.cpp)
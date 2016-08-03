cmake_minimum_required(VERSION 3.3)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(PROJECTNAME sar_dl_pgm)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54.0 COMPONENTS thread system filesystem log log_setup program_options REQUIRED)

include_directories(/usr/include/boost)

add_executable(img_process img_proc_main.cpp)
#add_executable(img_process file_process.c)
#add_executable(img_process system_call.cpp)
target_link_libraries(img_process ${Boost_LIBRARIES})
target_link_libraries(img_process /usr/lib/x86_64-linux-gnu/libjpeg.so)
cmake_minimum_required(VERSION 3.5)
project(baseball_pi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(curlpp REQUIRED)
include_directories(${curlpp_INCLUDE_DIRS})
set(LIBS ${LIBS} ${curlpp_LIBRARIES})

find_package(libcurl REQUIRED)
include_directories(${libcurl_INCLUDE_DIRS})
set(LIBS ${LIBS} ${libcurl_LIBRARIES})

find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

set(SOURCE_FILES main.cpp DataStructures/Game.cpp DataStructures/Game.h DataStructures/XMLMemoryUnit.cpp DataStructures/XMLMemoryUnit.h Tools/CURLTools.cpp Tools/CURLTools.h Tools/XMLppTools.cpp Tools/XMLppTools.h)
add_executable(baseball_pi ${SOURCE_FILES})
target_link_libraries(baseball_pi ${LIBS})

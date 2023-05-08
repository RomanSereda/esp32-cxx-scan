cmake_minimum_required(VERSION 3.16)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/experimental_cpp_component/include") 
list(APPEND EXTRA_COMPONENT_DIRS experimental_cpp_component)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(wenvmitter-esp-firmware)

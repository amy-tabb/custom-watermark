cmake_minimum_required(VERSION 3.0)

project(custom-watermark)

# set the flags, may want to add/change debugging or optimization (-O3) flags as appropriate
set(CMAKE_CXX_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -std=c++17")

add_executable(custom-watermark
custom-watermark.cpp
)

target_link_libraries(custom-watermark stdc++ m)

set_property(TARGET custom-watermark PROPERTY INSTALL_RPATH_USE_LINK_PATH TRUE)

install(TARGETS custom-watermark DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )


cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(geoViz)

find_package( OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( "ext/" )


file(STRINGS CMakeSources.txt SRC_LIST)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC_LIST})

add_subdirectory(drawing)
add_library( GLDRAWER SHARED GLDRAWER.cpp)
target_link_libraries(GLDRAWER ${OPENGL_LIBRARIES} glfw)
add_executable(helloWorld helloWorld.cpp)
target_link_libraries(helloWorld GLDRAWER ${OPENGL_LIBRARIES} glfw)

add_executable(imguiTest imguiTest.cpp)
target_link_libraries(imguiTest GLDRAWER ${OPENGL_LIBRARIES} glfw IMGUI)

add_executable(basicEnvironment basicEnvironment.cpp)
target_link_libraries(basicEnvironment GLDRAWER ${OPENGL_LIBRARIES} glfw IMGUI)
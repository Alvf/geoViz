cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(geoViz)

find_package( OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )

include_directories( "ext/" )
include_directories( "src/" )

set( IMGUI_SOURCES
		 ext/imgui-master/imgui.h
		 ext/imgui-master/imgui.cpp
		 ext/imgui-master/imgui_internal.h
		 ext/imgui-master/ImGuizmo.h
		 ext/imgui-master/ImGuizmo.cpp
		 ext/imgui-master/ImLightRig.h
		 ext/imgui-master/ImSequencer.h
		 ext/imgui-master/ImSequencer.cpp
		 ext/imgui-master/ImZoomSlider.h
		 ext/imgui-master/GraphEditor.h
		 ext/imgui-master/GraphEditor.cpp
		 ext/imgui-master/ImCurveEdit.h
		 ext/imgui-master/ImCurveEdit.cpp
		 ext/imgui-master/imgui_demo.cpp
		 ext/imgui-master/imgui_draw.cpp
		 ext/imgui-master/imgui_widgets.cpp
		 ext/imgui-master/imgui_tables.cpp
		 ext/imgui-master/imconfig.h
		 ext/imgui-master/backends/imgui_impl_glfw.h
		 ext/imgui-master/backends/imgui_impl_glfw.cpp
		 ext/imgui-master/backends/imgui_impl_opengl2.h
		 ext/imgui-master/backends/imgui_impl_opengl2.cpp
)

add_library(IMGUI SHARED ${IMGUI_SOURCES})

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLAD_GL "")
add_subdirectory("ext/glfw")
option( GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" ON )
if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

include_directories( "ext/imgui-master" )
include_directories( "ext/imgui-master/backends" )

add_subdirectory("src/")
add_subdirectory("apps/")
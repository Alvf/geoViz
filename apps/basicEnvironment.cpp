#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "drawing/GLDRAWER.h"
#include <iostream>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include "glfw/include/GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/constants.hpp"
#include "argparse.hpp"

GLFWwindow* _window;
VEC3 _startLoc, _anchorStart, _lookAt, _anchorLookAt, _up;
ImVec4 _clearColor;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void processMouseClickDrag(const ImGuiIO& io)
{
  _startLoc = _anchorStart + (_anchorLookAt - _anchorStart)*io.MouseWheel*0.01;
  if(ImGui::IsMouseDragging(1))
  {
    ImVec2 rightDrag = io.MouseDelta;
    VEC3 lookVec = _lookAt - _startLoc;
    VEC3 panLeft = _up.cross(lookVec).normalized();
    VEC3 panUp = lookVec.cross(panLeft).normalized();
    VEC3 transVec = rightDrag[0]*panLeft + rightDrag[1]*panUp;
    transVec *= 0.01;
    double goodOffset = (_anchorStart - _anchorLookAt).norm();
    _startLoc = (_anchorStart + transVec - _anchorLookAt).normalized()*goodOffset + _anchorLookAt;
  }
  if(ImGui::IsMouseDragging(2))
  {
    ImVec2 midDrag = io.MouseDelta;
    VEC3 lookVec = _lookAt - _startLoc;
    VEC3 panLeft = _up.cross(lookVec).normalized();
    VEC3 panUp = lookVec.cross(panLeft).normalized();
    VEC3 transVec = midDrag[0]*panLeft + midDrag[1]*panUp;
    transVec *= 0.01;
    _lookAt = _anchorLookAt + transVec;
    _startLoc = _anchorStart + transVec;
  }
  
  _anchorStart = _startLoc;
  _anchorLookAt = _lookAt;
}

void windowInit()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(1);

    // Create window with graphics context
    float main_scale = 2.0;
    _window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Local SHelix Viewer", nullptr, nullptr);
    if (_window == nullptr)
        exit(1);
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL2_Init();

    _startLoc = VEC3(1, 0, 0);
    _lookAt = VEC3(0, 0, 0);
    _up = VEC3(0,0,1);
    _anchorStart = _startLoc;
    _anchorLookAt = _lookAt;
}

void rendering()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(_clearColor.x * _clearColor.w, _clearColor.y * _clearColor.w, _clearColor.z * _clearColor.w, _clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);
    glLoadMatrixf(glm::value_ptr(projection));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 look = glm::lookAt(glm::vec3(_startLoc[0], _startLoc[1], _startLoc[2]),
                                    glm::vec3(_lookAt[0], _lookAt[1], _lookAt[2]), 
                                    glm::vec3(_up[0], _up[1], _up[2]));
    glLoadMatrixf(glm::value_ptr(look));

    drawAxes();

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glfwMakeContextCurrent(_window);
    glfwSwapBuffers(_window);

}

void uiElements(const ImGuiIO& io)
{
    // little background/fps checker
    {
        ImGui::Begin("utils");                        
        ImGui::ColorEdit3("clear color", (float*)&_clearColor); // Edit 3 floats representing a color

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // display settings
    {
        ImGui::Begin("display settings");                        
        ImGui::InputDouble("eye0", &_anchorStart[0]);
        ImGui::InputDouble("eye1", &_anchorStart[1]);
        ImGui::InputDouble("eye2", &_anchorStart[2]);
        ImGui::InputDouble("lookat0", &_lookAt[0]);
        ImGui::InputDouble("lookat1", &_lookAt[1]);
        ImGui::InputDouble("lookat2", &_lookAt[2]);
        ImGui::InputDouble("up0", &_up[0]);
        ImGui::InputDouble("up1", &_up[1]);
        ImGui::InputDouble("up2", &_up[2]);
        ImGui::End();
    }

}

void mainLoop()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;                   // using ImGui for IO (including mouse drag)
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    while (!glfwWindowShouldClose(_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(_window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        processMouseClickDrag(io);
        uiElements(io);

        // Rendering
        rendering();
    }
}

int main(int argc, char** argv)
{
    argparse::ArgumentParser parser("basic Environment");

    try {
    parser.parse_args(argc, argv); 
    }
    catch (const std::exception& err) {
    std::cerr << err.what() << std::endl;
    std::cerr << parser;
    std::exit(1);
    }
    
    windowInit();
    // Our state
    _clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    mainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();

    return 0;
}
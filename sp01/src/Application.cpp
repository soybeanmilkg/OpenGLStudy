#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Renderer.h"
#include "tests/TestTexture2D.h"
#include "tests/TestClearColor.h"
#include "tests/TestBatchRendering.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// OpenGL API 文档 https://docs.gl/

static void glfw_error_callback(int error, const char* description)
{
    std::cout << "[GLFW Error] " << error << ": " << description << '\n';
}

int main(void)
{
    glfwSetErrorCallback(glfw_error_callback);
    // 初始化 GLFW Initialize the library
    if (!glfwInit())
        return -1;

    /* 设置 OpenGL 版本和配置 */
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello OpenGL", NULL, NULL); // 创建一个窗口 Create a windowed mode window and its OpenGL context
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Make the window's context current
    glfwSwapInterval(1); // 启用垂直同步

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl; // 输出 OpenGL 版本

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    Renderer renderer; // 渲染器

    test::Test* currentTest;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->register_test<test::TestTexture2D>("2D Texture");
    testMenu->register_test<test::TestClearColor>("Clear Color");
    testMenu->register_test<test::TestBatchRendering>("Batch Rendering");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        currentTest->set_renderer(&renderer);
        currentTest->on_update(0.0f);
        currentTest->on_render();
        ImGui::Begin("Test");
        if (currentTest != testMenu && ImGui::Button("<-"))
        {
            delete currentTest;
            currentTest = testMenu;
        }
        currentTest->on_render_imgui();
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    if (currentTest != testMenu)
        delete testMenu;
    delete currentTest;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

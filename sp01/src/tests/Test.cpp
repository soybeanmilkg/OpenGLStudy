#include "Test.h"

#include "imgui/imgui.h"

namespace test
{
    void TestMenu::on_render_imgui()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        for (const auto& pair : m_Tests)
        {
            if (ImGui::Button(pair.first.c_str()))
                m_Current = pair.second();
        }
    }
}
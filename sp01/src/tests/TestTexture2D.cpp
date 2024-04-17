#include "TestTexture2D.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test
{
    TestTexture2D::TestTexture2D()
            :m_TransfromA(100, 100, 0), m_TransfromB(200, 200, 0)
    {
        // 顶点数据
        float positions[] = {
                -50.0f, -50.0f, 0.0f, 0.0f,
                50.5f, -50.0f, 1.0f, 0.0f,
                50.5f,  50.5f, 1.0f, 1.0f,
                -50.0f,  50.5f, 0.0f, 1.0f,
        };
        // 顶点索引数据
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
        };

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float)); // 创建顶点缓存
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 3); //创建顶点索引缓存
        m_Shader = std::make_unique<Shader>("resources/shaders/basic.shader");
        m_Texture = std::make_unique<Texture>("resources/textures/avatar.png");

        m_VertexArray = std::make_unique<VertexArray>();
        m_Layout = std::make_unique<VertexLayout>();
        m_Layout->push<float>(2);
        m_Layout->push<float>(2);
        m_VertexArray->add_buffer(*m_VertexBuffer, *m_Layout);

        m_Proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f); // 投影矩阵

        m_Texture->bind();
        m_Shader->bind(); // 要 bind 之后才能设置 uniform 变量
        m_Shader->set_uniform1i("u_Texture", 0); // 设置纹理
    }

    TestTexture2D::~TestTexture2D()
    {}

    void TestTexture2D::on_update(float deltatime)
    {}

    void TestTexture2D::on_render()
    {
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TransfromA);
            glm::mat4 mvp = m_Proj * model;
            m_Shader->bind();
            m_Shader->set_uniform_mat4f("u_MVP", mvp);
            m_Renderer->draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TransfromB);
            glm::mat4 mvp = m_Proj * model;
            m_Shader->bind();
            m_Shader->set_uniform_mat4f("u_MVP", mvp);
            m_Renderer->draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::on_render_imgui()
    {
        ImGui::SliderFloat("Transfrom A X", &m_TransfromA.x, 0.0f, 1280.0f);
        ImGui::SliderFloat("Transfrom A Y", &m_TransfromA.y, 0.0f, 720.0f);
        ImGui::SliderFloat("Transfrom B X", &m_TransfromB.x, 0.0f, 1280.0f);
        ImGui::SliderFloat("Transfrom B Y", &m_TransfromB.y, 0.0f, 720.0f);
    }
}

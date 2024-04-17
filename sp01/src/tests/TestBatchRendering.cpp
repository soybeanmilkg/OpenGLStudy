#include "TestBatchRendering.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"



static constexpr int MAX_VERTEX_COUNT = 1000;

namespace test
{
    TestBatchRendering::TestBatchRendering()
    {
        constexpr int indexCount = static_cast<int>(MAX_VERTEX_COUNT * 1.5);
        unsigned int indices[indexCount] = {};
        unsigned int offset = 0;
        for (size_t i = 0; i < MAX_VERTEX_COUNT / 4; i++)
        {
            int index = i * 6;
            indices[index + 0] = 0 + offset;
            indices[index + 1] = 1 + offset;
            indices[index + 2] = 2 + offset;
            indices[index + 3] = 2 + offset;
            indices[index + 4] = 3 + offset;
            indices[index + 5] = 0 + offset;

            offset += 4;
        }
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MAX_VERTEX_COUNT * sizeof(test::TestBatchRendering::Vertex), GL_DYNAMIC_DRAW);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, indexCount);

        m_VertexArray = std::make_unique<VertexArray>();
        m_Layout = std::make_unique<VertexLayout>();
        m_Layout->push<glm::vec2>(1);
        m_Layout->push<glm::vec4>(1);
        m_Layout->push<glm::vec2>(1);
        m_Layout->push<float>(1);
        m_VertexArray->add_buffer(*m_VertexBuffer, *m_Layout);

        m_Shader = std::make_unique<Shader>("resources/shaders/batch.shader");
        m_Shader->bind();
        m_Proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f); // 投影矩阵
        m_Shader->set_uniform_mat4f("u_MVP", m_Proj);

        m_Textures[0] = std::make_unique<Texture>("resources/textures/avatar.png");
        m_Textures[1] = std::make_unique<Texture>("resources/textures/favicon.png");

        m_Textures[0]->bind(0);
        m_Textures[1]->bind(1);
        int samplers[2] = { 0, 1 };
        m_Shader->set_uniform1iv("u_Textures", 2, samplers);

        m_Vertices = new Vertex[1000];
    }

    TestBatchRendering::~TestBatchRendering()
    {
        delete[] m_Vertices;
    }

    void TestBatchRendering::on_update(float deltatime)
    {}

    test::TestBatchRendering::Vertex* TestBatchRendering::draw_square(int x, int y, float slot)
    {
        test::TestBatchRendering::Vertex& v0 = m_Vertices[m_Index * 4];
        v0.position = glm::vec2(-50.0f + x * 100, -50.0f + y * 100);
        v0.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        v0.texCoord = glm::vec2(0.0f, 0.0f);
        v0.texIndex = slot;

        test::TestBatchRendering::Vertex& v1 = m_Vertices[m_Index * 4 + 1];
        v1.position = glm::vec2(50.0f + x * 100, -50.0f + y * 100);
        v1.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        v1.texCoord = glm::vec2(1.0f, 0.0f);
        v1.texIndex = slot;

        test::TestBatchRendering::Vertex& v2 = m_Vertices[m_Index * 4 + 2];
        v2.position = glm::vec2(50.0f + x * 100, 50.0f + y * 100);
        v2.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        v2.texCoord = glm::vec2(1.0f, 1.0f);
        v2.texIndex = slot;

        test::TestBatchRendering::Vertex& v3 = m_Vertices[m_Index * 4 + 3];
        v3.position = glm::vec2(-50.0f + x * 100, 50.0f + y * 100);
        v3.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        v3.texCoord = glm::vec2(0.0f, 1.0f);
        v3.texIndex = slot;

        m_Index++;
        return &v0;
    }

    void TestBatchRendering::on_render()
    {
        m_Index = 0;
        for (size_t x = 0; x < 15; x++)
        {
            for (size_t y = 0; y < 8; y++)
            {
                draw_square(x, y, ((x * 9) + y) % 2);
            }
        }

        m_VertexBuffer->bind(m_Vertices, MAX_VERTEX_COUNT * sizeof(Vertex), GL_DYNAMIC_DRAW);
        m_Renderer->draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    void TestBatchRendering::on_render_imgui()
    {}
}

#pragma once
#include "Test.h"

#include <memory>

#include "glm/glm.hpp"

class Texture;
class VertexBuffer;
class IndexBuffer;
class Shader;
class VertexArray;
class VertexLayout;

struct Vertex;

namespace test
{
    class TestBatchRendering : public Test
    {
    private:
        struct Vertex
        {
            glm::vec2 position;
            glm::vec4 color;
            glm::vec2 texCoord;
            float texIndex;
        };

        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexLayout> m_Layout;

        std::unique_ptr<Texture> m_Textures[2];
        std::unique_ptr<Shader> m_Shader;

        glm::mat4 m_Proj;

        test::TestBatchRendering::Vertex* m_Vertices;
        int m_Index = 0;
    public:
        TestBatchRendering();
        ~TestBatchRendering();

        Vertex* draw_square(int x, int y, float slot);

        void on_update(float deltatime);
        void on_render();
        void on_render_imgui();
    };
}


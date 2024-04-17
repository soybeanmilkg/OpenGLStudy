#pragma once
#include "Test.h"

#include <memory>

#include "glm/glm.hpp"

class VertexBuffer;
class IndexBuffer;
class Shader;
class Texture;
class VertexArray;
class VertexLayout;

namespace test
{
    class TestTexture2D : public Test
    {
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexLayout> m_Layout;

        glm::mat4 m_Proj;

        glm::vec3 m_TransfromA, m_TransfromB;
    public:
        TestTexture2D();
        ~TestTexture2D();

        void on_update(float deltatime) override;
        void on_render() override;
        void on_render_imgui() override;
    private:
    };
}



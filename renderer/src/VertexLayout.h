#pragma once

#include <vector>

#include "Renderer.h"

#include "glm/glm.hpp"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class VertexLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    int m_Stride;

public:
    VertexLayout() :m_Stride(0) {}

    template<typename T>
    void push(unsigned int count)
    {
        /*
        * https://learn.microsoft.com/zh-cn/cpp/overview/cpp-conformance-improvements?view=msvc-170
        * 
        * 在 Visual Studio 2022 版本 17.1 及更高版本中，
        * 如果与 static_assert 关联的表达式不是依赖性表达式，
        * 则编译器会在分析表达式时对其进行计算。
        * 如果表达式的计算结果为 false，编译器将发出错误。
        * 以前，如果 static_assert 在一个函数模板的主体内（或在一个类模板的成员函数的主体内），
        * 编译器就不会执行这种分析。这是一项源中断性变更。
        * 它适用于任何表示 /permissive- 或 /Zc:static_assert 的模式。
        * 可以使用 /Zc:static_assert- 编译器选项来禁用此行为更改。
        *
        * CMake 使用 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:static_assert-") 没有效果，不知道是不是哪里配错了
        */
        // static_assert(false);
        ASSERT(false)
    }

    template<>
    void push<float>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::get_size_of_type(GL_FLOAT);
    }

    template<>
    void push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += count * VertexBufferElement::get_size_of_type(GL_UNSIGNED_BYTE);
    }

    template<>
    void push<glm::vec2>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count * 2, GL_FALSE });
        m_Stride += count * 2 * VertexBufferElement::get_size_of_type(GL_FLOAT);
    }

    template<>
    void push<glm::vec3>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count * 3, GL_FALSE });
        m_Stride += count * 3 * VertexBufferElement::get_size_of_type(GL_FLOAT);
    }

    template<>
    void push<glm::vec4>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count * 4, GL_FALSE });
        m_Stride += count * 4 * VertexBufferElement::get_size_of_type(GL_FLOAT);
    }

    const std::vector<VertexBufferElement>& get_elements()const { return m_Elements; }
    int get_stride() const { return m_Stride; }
};

#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::add_buffer(const VertexBuffer& buffer, const VertexLayout& layout) const
{
    bind();
    buffer.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for (size_t i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i)); // 启用顶点属性
        GLCall(glVertexAttribPointer(
                i,
                element.count,
                element.type,
                element.normalized,
                layout.get_stride(),
                reinterpret_cast<const void*>(offset)
        )); // 描述顶点属性
        offset += element.count * VertexBufferElement::get_size_of_type(element.type);
    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::undind() const
{
    GLCall(glBindVertexArray(0));
}

#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size)
{
    GLCall(glGenBuffers(1, &m_RenderID)); // 创建一个缓存
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID)); // 绑定缓存。就是选择渲染这个缓存里的内容
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // 复制顶点数据到缓存
}

VertexBuffer::VertexBuffer(const void* data, const unsigned int& size, unsigned int type)
{
    GLCall(glGenBuffers(1, &m_RenderID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, type));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}

void VertexBuffer::bind(const void* data, const unsigned int& size, unsigned int type) const
{
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, type));
}

void VertexBuffer::unbind() const
{
    GLCall(glGenBuffers(1, 0));
}

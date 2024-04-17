#pragma once
class VertexBuffer
{
private:
    unsigned int m_RenderID;

public:
    VertexBuffer(const void* data, const unsigned int& size);
    VertexBuffer(const void* data, const unsigned int& size, unsigned int type);
    ~VertexBuffer();

    void bind() const;
    void bind(const void* data, const unsigned int& size, unsigned int type) const;
    void unbind() const;
};

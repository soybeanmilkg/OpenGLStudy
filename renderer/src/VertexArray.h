#pragma once

class VertexBuffer;
class VertexLayout;

class VertexArray
{
private:
    unsigned int m_RenderID;
public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBuffer& buffer, const VertexLayout& layout) const;

    void bind() const;
    void undind() const;
};


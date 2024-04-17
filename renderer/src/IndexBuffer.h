#pragma once
class IndexBuffer
{
private:
    unsigned int m_RenderID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* indices, const unsigned int& count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int get_count() const { return m_Count; }
};


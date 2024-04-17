#pragma once

#include <string>

#include "Renderer.h"

class Texture
{
private:
    unsigned int m_RenderID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP; // 宽、高、BPP: bit per pixel 每位像素大小
public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    inline int get_width() { return m_Width; }
    inline int get_height() { return m_Height; }
};


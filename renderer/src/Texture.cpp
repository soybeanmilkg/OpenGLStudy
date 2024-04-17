#include "Texture.h"

#include "stb/stb_image.h"

Texture::Texture(const std::string& filepath)
    :m_RenderID(0), m_FilePath(filepath), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1); // 翻转图像加载
    m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    GLCall(glGenTextures(1, &m_RenderID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

    /*
    * 来自通义千问的解释
    * 
    * 这段代码是在设置OpenGL纹理参数。具体来说：
    * glTexParameteri函数是用来设置某个已绑定纹理的目标参数的。这里的纹理目标是GL_TEXTURE_2D，表示针对2D纹理进行参数设置。
    * 
    * GL_TEXTURE_MIN_FILTER：设置纹理的缩小过滤方式。GL_LINEAR表示采用线性插值进行纹理缩小采样，当纹理被映射到比其本身小的区域时，会混合周围的像素颜色以得到平滑的效果。
    * GL_TEXTURE_MAG_FILTER：设置纹理的放大过滤方式。同样设置为GL_LINEAR，意味着当纹理被放大显示时，也会采用线性插值进行采样，以保证放大后的纹理相对平滑。
    * GL_TEXTURE_WRAP_S：设置纹理在S轴（水平方向）上的环绕方式。GL_CLAMP_TO_EDGE表示当纹理坐标超出[0, 1]范围时，取最接近边缘的颜色值，不会重复纹理图像。
    * GL_TEXTURE_WRAP_T：设置纹理在T轴（垂直方向）上的环绕方式。同样设置为GL_CLAMP_TO_EDGE，含义与S轴相同。
    * 
    * 总结起来，这段代码的作用就是设置一个2D纹理，使其在缩小和放大时都采用线性过滤，并且在纹理坐标超过边界时，边缘颜色不再重复而是固定在边缘像素上。
    * 这些设置对于避免纹理拉伸和变形时产生锯齿和不自然的效果很有帮助。
    */
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer)); // 把内存里的数据传到显卡
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RenderID));
}

void Texture::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

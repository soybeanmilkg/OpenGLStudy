#include "Renderer.h"

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void gl_clear_error()
{
    while (glGetError() != GL_NO_ERROR);
}

bool gl_error_log(const char* funcname, const char* filepath, int line)
{
    while (unsigned int error = glGetError())
    {
        std::cout << "[GLERROR] error code: (" << error << ") " << funcname
                  << " in file: " << filepath << ": " << line << '\n';
        return false;
    }

    return true;
}

Renderer::Renderer()
{
    /*
    * 来自通义千问
    *
    * 这两行OpenGL函数调用用于启用并配置混合功能（Blending）。
    * 1. `GLCall(glEnable(GL_BLEND));`
    *    这行代码启用OpenGL的混合功能。混合是指在绘制物体时，将源颜色与帧缓冲区中已有的颜色按照一定规则进行混合，从而实现透明度、抗锯齿等效果。
    *    在开启了混合之后，每个像素的颜色不仅取决于当前要绘制的颜色，还受到已经存在于屏幕上的颜色的影响。
    * 2. `GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));`
    *    这行代码设置了混合函数。`glBlendFunc`函数接受两个参数，分别代表源因子（Source Factor）和目标因子（Destination Factor）。
    *        - `GL_SRC_ALPHA` 表示源颜色的alpha通道值作为参与混合的因子。
    *        - `GL_ONE_MINUS_SRC_ALPHA` 表示目标颜色的原alpha通道值减去源颜色alpha通道值得到的值作为参与混合的因子。
    * 当使用这种混合模式时，新绘制的像素颜色会根据它的alpha值与背景颜色进行混合。具体计算公式为：(src.rgb * src.a) + (dst.rgb * (1-src.a))。
    * 这种混合模式常用于实现半透明效果，其中源颜色的alpha值决定了其透明度。
    */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Renderer::~Renderer()
{}

void Renderer::clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.bind();
    ib.bind();
    shader.bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr)); // DrawCall
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib) const {
    va.bind();
    ib.bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr)); // DrawCall
}

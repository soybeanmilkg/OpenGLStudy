#pragma once

#include "glad/include/glad/glad.h"

#define ASSERT(x) if(!(x)) { __debugbreak(); }
#define GLCall(x) gl_clear_error();\
    x;\
    ASSERT(gl_error_log(#x, __FILE__, __LINE__))

/// <summary>
/// 清理 OpenGL 错误
/// </summary>
void gl_clear_error();

/// <summary>
/// 打印 OpenGL 错误
/// </summary>
/// <param name="funcname">方法名</param>
/// <param name="filepath">文件路径</param>
/// <param name="line">错误行</param>
/// <returns></returns>
bool gl_error_log(const char* funcname, const char* filepath, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear() const;
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void draw(const VertexArray& va, const IndexBuffer& ib) const;
};

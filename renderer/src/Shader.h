#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
private:
    unsigned int m_RenderID;
    std::string m_FilePath;
    std::unordered_map<const char*, int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void set_uniform1i(const char* name, int v1);
    void set_uniform1f(const char* name, float v1);
    void set_uniform4f(const char* name, float v1, float v2, float v3, float v4);
    void set_uniform_mat4f(const char* name, glm::mat4& matrix);
    void set_uniform1iv(const char* name, int count, int* value);
private:
    /// <summary>
    /// 解析 shader 文件
    /// </summary>
    /// <param name="filepath">文件路劲</param>
    /// <returns>vertex shader 和 fragment shaher 源码字符串</returns>
    std::tuple<std::string, std::string> parse_shader(const std::string& filepath);

    /// <summary>
    /// 编译着色器
    /// </summary>
    /// <param name="type">着色器类型</param>
    /// <param name="source">源码字符串</param>
    /// <returns>编译后的内容 id</returns>
    unsigned int compile_shader(unsigned int type, const std::string& source);

    /// <summary>
    /// 创建着色器程序
    /// </summary>
    /// <param name="vertexShader">vertex shader 源码字符串</param>
    /// <param name="fragmentShader">fragment shader 源码字符串</param>
    /// <returns>着色器程序 id</returns>
    unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);

    int get_uniform_location(const char* name);
};


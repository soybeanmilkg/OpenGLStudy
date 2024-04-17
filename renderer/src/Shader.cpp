#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>

#include "Renderer.h"

enum ShaderType
{
    None = -1,
    Vertex = 0,
    Fragment = 1,
};

Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath)
{
    auto [vertexShader, fragmentShader] = parse_shader(filepath);
    m_RenderID = create_shader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RenderID));
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RenderID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::set_uniform1i(const char* name, int v1)
{
    GLCall(glUniform1i(get_uniform_location(name), v1));
}

void Shader::set_uniform1f(const char* name, float v1)
{
    GLCall(glUniform1f(get_uniform_location(name), v1));
}

void Shader::set_uniform4f(const char* name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(get_uniform_location(name), v1, v2, v3, v4)); // 设置 uniform 变量
}

void Shader::set_uniform_mat4f(const char* name, glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::set_uniform1iv(const char* name, int count, int* value)
{
    GLCall(glUniform1iv(get_uniform_location(name), count, value));
}

std::tuple<std::string, std::string> Shader::parse_shader(const std::string& filepath)
{
    ShaderType type = ShaderType::None;
    std::string line;
    std::stringstream ss[2];
    std::fstream file(filepath);
    while (getline(file, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::Vertex;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::Fragment;
            }
        }
        else if (type != ShaderType::None)
        {
            ss[type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
    // 创建着色器
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    // 设置着色器源码
    GLCall(glShaderSource(id, 1, &src, nullptr));
    // 编译着色器
    GLCall(glCompileShader(id));

    int result;
    // 获得着色器编译结果
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) // 着色器编译错误
    {
        int length;
        // 获得日志信息长度
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        // _malloca: 在堆栈上分配内存
        char* message = static_cast<char*>(_malloca(length * sizeof(char)));
        // 获得日志信息
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        const char* shaderType = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
        std::cout << "Failed to compile " << shaderType << " shader! " << message << std::endl;
        // 删除着色器
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string& vertexShader, const std::string& fragmentShader)
{
    // 创建着色器程序
    GLCall(unsigned int program = glCreateProgram());
    // 编译顶点着色器、片段着色器
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    // 附加顶点着色器、片段着色器
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    // 链接着色器程序
    GLCall(glLinkProgram(program));
    // 验证着色器程序
    GLCall(glValidateProgram(program));

    // 删除顶点着色器、片段着色器
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int Shader::get_uniform_location(const char* name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RenderID, name)); // 获得 uniform 变量
    if (location == -1)
        std::cout << "Warning! Not found uniform " << name << " location.\n";

    m_UniformLocationCache[name] = location;
    return location;
}

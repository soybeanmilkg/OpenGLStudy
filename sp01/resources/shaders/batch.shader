#shader vertex
// 顶点着色器源码
#version 330 core
    
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_Color = color;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
}

#shader fragment
// 片段着色器源码
#version 330 core
    
layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
    color = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
}

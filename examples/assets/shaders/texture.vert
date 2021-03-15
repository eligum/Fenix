#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_ProjView;
uniform mat4 u_Transform;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = a_TexCoord;
    gl_Position = u_ProjView * u_Transform * vec4(a_Pos , 1.0);
}

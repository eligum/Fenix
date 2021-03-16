#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ProjView;
uniform mat4 u_Transform;

out vec4 v_Color;

void main()
{
    v_Color = a_Color;
    gl_Position = u_ProjView * u_Transform * vec4(a_Pos , 1.0);
}

#type fragment
#version 330 core

in vec4 v_Color;

out vec4 color;

void main()
{
    color = v_Color;
}

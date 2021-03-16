#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;

uniform mat4 u_ProjView;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ProjView * u_Transform * vec4(a_Pos , 1.0);
}

#type fragment
#version 330 core

uniform vec4 u_Color;

out vec4 color;

void main()
{
    color = u_Color;
}

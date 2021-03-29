#type vertex
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

#type fragment
#version 330 core

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform float u_TexCoordMult;
uniform sampler2D u_Texture;

out vec4 color;

void main()
{
    color = texture(u_Texture, v_TexCoord * u_TexCoordMult) * u_Color;
}

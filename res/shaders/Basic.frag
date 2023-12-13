#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	vec4 texColor = texture(diffuse0, v_TexCoord);
	color = texColor;
};
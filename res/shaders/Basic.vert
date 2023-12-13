#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
	vec4 newPosition = u_Projection * u_View * u_Model * position;

	gl_Position = vec4(newPosition.xyzw);
	v_TexCoord = texCoord;
};
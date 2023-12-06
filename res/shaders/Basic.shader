#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 3) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP; //ModelViewProjectionmatrix

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{

	vec4 newPosition = u_Projection * u_View * u_Model * position;
	gl_Position = vec4(newPosition.xyzw);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;

uniform sampler2D u_Texture;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	vec4 texColor = texture(diffuse0, v_TexCoord);
	color = texColor;
};
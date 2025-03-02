#version 330 core

layout (location = 0) in vec3 aPos;
layout (location =1) in vec2 aTexture;


out vec2 texCoord;
uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	mat4 camMat=projection * view;
	gl_Position =camMat * model * vec4(aPos, 1.0);
	texCoord=aTexture;
}
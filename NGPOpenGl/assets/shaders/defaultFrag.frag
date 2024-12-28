#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D tex0;
uniform int isColor;
uniform vec3 setColor;
void main()
{
	if(isColor == 1)
	FragColor = vec4(setColor, 1.0f);
	else
	FragColor = texture(tex0,texCoord);
}
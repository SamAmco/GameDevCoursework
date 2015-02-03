#version 150 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time;

in  vec3 position;
in  vec2 texCoord;
in  vec4 colour;

out Vertex	{
	vec2 texCoord;
	vec4 colour;
} OUT;

void main(void)	
{
	mat4 scale = mat4((sin(time) / 2) + 0.5);
	scale[3][3] = 1.0;
	gl_Position		= projMatrix * viewMatrix * modelMatrix * scale * vec4(position, 1.0);
	
	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}
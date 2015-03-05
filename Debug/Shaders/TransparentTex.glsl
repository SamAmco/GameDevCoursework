#version 150 core

uniform sampler2D tex1;

in Vertex 
{
	vec2 texCoord;
} IN;

out vec4 gl_FragColor;

void main(void) 
{
	gl_FragColor = texture(tex1 , IN.texCoord);
}
















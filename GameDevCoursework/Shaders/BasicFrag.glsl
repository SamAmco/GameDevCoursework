#version 330 core

uniform sampler2D tex1;

in Vertex	
{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	
{	
	gl_FragColor = texture2D(tex1, IN.texCoord);//IN.colour;
}
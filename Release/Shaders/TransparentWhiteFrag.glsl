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
	vec4 col = texture2D(tex1, IN.texCoord);
	
	col.a = IN.colour.a;
	
	gl_FragColor = col;
}
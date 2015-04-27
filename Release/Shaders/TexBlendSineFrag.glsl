#version 330 core

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float time;

in Vertex	
{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	
{	
	vec4 tex1Col = texture2D(tex1, IN.texCoord);
	vec4 tex2Col = texture2D(tex2, IN.texCoord);
	float l = (sin(time) / 2) + 0.5;
	gl_FragColor = (tex1Col * l) + (tex2Col * (1.0 - l));
}
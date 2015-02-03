#version 330 core

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;

in Vertex	
{
	vec2 texCoord;
	vec4 colour;
} IN;

out vec4 gl_FragColor;

void main(void)	
{	
	vec4 gray = texture2D(tex2, IN.texCoord);
	float amount = (gray.r + gray.g + gray.b) / 3.0;
	vec4 col1 = texture2D(tex1, IN.texCoord);
	vec4 col2 = texture2D(tex3, IN.texCoord);
	gl_FragColor = (col1 * amount) + (col2 * (1.0 - amount));
}
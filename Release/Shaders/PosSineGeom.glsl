# version 330 core

layout ( triangles ) in;
layout ( triangle_strip , max_vertices = 3) out;

uniform float time;

in Vertex 
{
	vec4 colour;
	vec2 texCoord;
} IN [];

out Vertex 
{
	vec4 colour;
	vec2 texCoord;
} OUT;

void main () 
{	
	for (int i = 0; i < gl_in.length (); ++ i ) 
	{
		float t = sin(length(gl_in[i].gl_Position));
		OUT.colour = IN[i].colour;
		OUT.texCoord = IN[i].texCoord;
		
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x += t;
		gl_Position.y += t;
		EmitVertex();
	}
	EndPrimitive();
}

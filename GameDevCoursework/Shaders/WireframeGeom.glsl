# version 330 core

layout ( triangles ) in;
layout ( line_strip , max_vertices = 10) out;

uniform float time;
uniform vec3 lightPos;

in Vertex 
{
	vec4 colour;
	vec2 texCoord;
} IN [];

out Vertex 
{
	vec4 colour;
} OUT;

void main () 
{
	vec4 projOrig = vec4(lightPos,0);
	OUT.colour = vec4(1,1,1,1);
	
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
	
	OUT.colour = vec4(1,1,1,1);
	gl_Position = projOrig;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = projOrig;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();
	EndPrimitive();
	
	gl_Position = projOrig;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}

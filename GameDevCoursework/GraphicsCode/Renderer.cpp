
#include "Renderer.h"
#include "Matrix3.h"
#include <time.h>
#include <SOIL.h>

Renderer::Renderer() 
{
	// CSC3224 NCODE  Samuel Amantea-Collins 110148685 
	light.colour = Vector3(1,1,1);
	light.position = Vector3(0,0,0);
	light.radius = 0;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//TODO: at the moment the cubemap is just hard coded, but this should be passed in to the renderer
	//or perhaps swappable

	//load the cubemap
	quad = Mesh::GenerateQuad();
	skyBoxShader = new Shader("Shaders/skyBoxVertex.glsl", "Shaders/skyBoxFragment.glsl");
	cubeMap = SOIL_load_OGL_cubemap(
		"Textures/checkered_left.jpg", "Textures/checkered_right.jpg",
		"Textures/checkered_top.JPG", "Textures/checkered_top.JPG",
		"Textures/checkered_back.jpg", "Textures/checkered_front.jpg",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID, 0);
	skyBoxShader->LinkProgram();
	// CSC3224 NCODE BLOCK ENDS
}

Renderer::~Renderer(void)	
{
	// CSC3224 NCODE  Samuel Amantea-Collins 110148685 
	delete skyBoxShader;
	delete quad;
	// CSC3224 NCODE BLOCK ENDS
}

void	Renderer::RenderScene() 
{
	DrawSkyBox();
	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i )
	{
		Render(*(*i));
	}
}

// CSC3224 NCODE  Samuel Amantea-Collins 110148685 
void Renderer::DrawSkyBox()
{
	//before we draw the rest of the scene, we draw the cubemap with no depth,
	//such that everything else will be drawn in front
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	glUseProgram(skyBoxShader->GetShaderProgram());
	
	UpdateShaderMatrices(skyBoxShader->GetShaderProgram());
	quad->Draw();
	
	glUseProgram(0);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);
}
// CSC3224 NCODE BLOCK ENDS

void Renderer::SetMainLight(Vector3 colour, Vector3 position, float radius)
{
	light.colour = colour;
	light.position = position;
	light.radius = radius;
}

void Renderer::UpdateShaderMatrices(GLuint program)	
{
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, (float*)&viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false, (float*)&projMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "textureMatrix"), 1, false, (float*)&textureMatrix);
}

void	Renderer::Render(const RenderObject &o) 
{
	modelMatrix = o.GetWorldTransform();

	if(o.GetShader() && o.GetMesh()) 
	{
		GLuint program = o.GetShader()->GetShaderProgram();
		
		glUseProgram(program);

		UpdateShaderMatrices(program);

		Matrix3 rotation = Matrix3(viewMatrix);
		Vector3 invCamPos = viewMatrix.GetPositionVector();
		Vector3 camPos = rotation * -invCamPos; 

		glUniform3fv(glGetUniformLocation(program, "cameraPos"), 1, (float*)&camPos);
		glUniform1f(glGetUniformLocation(program, "time"), ((float)clock()) / 1000.0);
		glUniform3fv(glGetUniformLocation(program, "lightColour"), 1, (float*) &light.colour);
		glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, (float*) &light.position);
		glUniform1f(glGetUniformLocation(program, "lightRadius"), light.radius);

		o.Draw();

		glUseProgram(0);
	}

	for(vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().end(); ++i ) 
	{
		Render(*(*i));
	}
}

void	Renderer::UpdateScene(float msec) 
{
	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) 
	{
		(*i)->Update(msec);
	}
}
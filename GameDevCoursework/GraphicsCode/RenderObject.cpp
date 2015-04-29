
#include "RenderObject.h"
#include <time.h>

RenderObject::RenderObject(void)	
{
	mesh	= NULL;
	shader = NULL;
	textures = vector<GLuint>();
	parent  = NULL;
}

RenderObject::RenderObject(MeshResource*m, MaterialResource*mat) 
{
	mesh	= m->mesh;
	shader = mat->shader;
	textures = vector<GLuint>();
	parent  = NULL;
}

void RenderObject::Update(float msec) 
{
	if(parent)
		worldTransform = parent->modelMatrix * modelMatrix;
	else
		worldTransform = modelMatrix;

	for(vector<RenderObject*>::const_iterator i = children.begin(); i != children.end(); ++i )
		(*i)->Update(msec);
}

void RenderObject::Draw() const 
{
	if(mesh) 
	{
		if (textures.size() > 0 && textures[0])
		{
			glUniform1i(glGetUniformLocation(shader->GetShaderProgram(), "tex1"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[0]);
		}
		if (textures.size() > 1 && textures[1])
		{
			glUniform1i(glGetUniformLocation(shader->GetShaderProgram(), "tex2"), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[1]);
		}
		if (textures.size() > 2 && textures[2])
		{
			glUniform1i(glGetUniformLocation(shader->GetShaderProgram(), "tex3"), 2);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, textures[2]);
		}
		mesh->Draw();
	}
}
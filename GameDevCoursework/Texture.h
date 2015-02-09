#pragma once
#include <GL\glew.h>
#include "Resource.h"

class Texture : Resource 
{
public:
	Texture(GLuint tex);
	GLuint getGLuint() const { return tex; } 
	~Texture();
private:
	GLuint tex;
};


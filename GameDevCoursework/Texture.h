#pragma once
#include <GL\glew.h>
#include "Resource.h"
#include <string>

using namespace std;

class Texture : Resource 
{
public:
	Texture() { };
	Texture(string, GLuint);
	GLuint getGLuint() const { return tex; } 
	string getName() const { return name; }
	bool hasLoaded() const { return loaded; }
	~Texture();
private:
	string name;
	GLuint tex;
	bool loaded = false;
};


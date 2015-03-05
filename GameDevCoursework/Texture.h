//File Written by Samuel Amantea-Collins
#pragma once
#include <GL\glew.h>
#include <string>

using namespace std;

//This stores the name of a texture associated with it's position in graphics memory.
//This class should only be created by the TextureManager. Has loaded is helpful if the
//TextureManager has not been able to find the texture, because it still returns a pointer
//to a Texture object.
class Texture 
{
public:
	Texture() { };
	Texture(string name, GLuint tex)
	{
		this->tex = tex;
		this->name = name;
		this->loaded = true;
	}
	const GLuint& getGLuint() const { return tex; } 
	string getName() const { return name; }
	bool hasLoaded() const { return loaded; }
	~Texture(){}
private:
	string name;
	GLuint tex;
	bool loaded = false;
};


#pragma once
#include <GL\glew.h>
#include <string>

using namespace std;

class Texture 
{
public:
	Texture() { };
	Texture(string, GLuint);
	const GLuint& getGLuint() const { return tex; } 
	string getName() const { return name; }
	bool hasLoaded() const { return loaded; }
	~Texture();
private:
	string name;
	GLuint tex;
	bool loaded = false;
};


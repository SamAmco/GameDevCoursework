#include "stdafx.h"
#include "Texture.h"

using namespace std;


Texture::Texture(string name, GLuint tex)
{
	this->name = name;
	this->tex = tex;
	this->loaded = true;
}


Texture::~Texture()
{
}

//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "Texture.h"

using namespace std;


Texture::Texture(string name, GLuint tex)
{
	this->tex = tex;
	this->name = name;
	this->loaded = true;
}


Texture::~Texture()
{
}

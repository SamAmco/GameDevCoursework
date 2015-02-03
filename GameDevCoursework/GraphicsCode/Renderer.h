#pragma once

#include "RenderObject.h"

#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/System/String.hpp>


using std::vector;
 
struct Light
{
	Vector3 position;
	float radius;
	Vector3 colour;
};

class Renderer : public sf::Window
{
public:
	Renderer(sf::VideoMode mode, const sf::String& title, 
		sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	~Renderer(void);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void	UpdateScene(float msec);

	void	AddRenderObject(RenderObject &r) 
	{
		renderObjects.push_back(&r);
	}

	void SetMainLight(Vector3 colour, Vector3 position, float radius);

	static GLuint LoadTexture(std::string name);

protected:

	void UpdateShaderMatrices(GLuint program);

	Matrix4 projMatrix;		//Projection matrix
	Matrix4 modelMatrix;	//Model matrix. NOT MODELVIEW
	Matrix4 viewMatrix;		//View matrix
	Matrix4 textureMatrix;	//Texture matrix

	vector<RenderObject*> renderObjects;
	Light light;
};


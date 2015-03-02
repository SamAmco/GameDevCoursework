#pragma once

#include "RenderObject.h"

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
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

class Renderer
{
public:
	Renderer();
	~Renderer(void);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void DrawSkyBox();

	virtual void	UpdateScene(float msec);

	void	AddRenderObject(RenderObject* r) 
	{
		renderObjects.push_back(r);
	}
	void RemoveRenderObject(RenderObject* r)
	{
		for (auto ro = renderObjects.begin(); ro != renderObjects.end(); ro++)
		{
			if (*ro == r)
			{
				renderObjects.erase(ro);
				break;
			}
		}
	}
	void	SetProjectionMatrix(Matrix4 m)
	{
		projMatrix = m;
	}

	Matrix4 viewMatrix;		//View matrix

	void SetMainLight(Vector3 colour, Vector3 position, float radius);

protected:

	void UpdateShaderMatrices(GLuint program);

	Matrix4 projMatrix;		//Projection matrix
	Matrix4 modelMatrix;	//Model matrix. NOT MODELVIEW
	Matrix4 textureMatrix;	//Texture matrix

	Shader* skyBoxShader;
	GLuint cubeMap;
	Mesh* quad;

	vector<RenderObject*> renderObjects;
	Light light;
};


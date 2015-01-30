#pragma once
#include "../nclgl/OGLRenderer.h"

#include "RenderObject.h"

#include <vector>

using std::vector;

struct Light
{
	Vector3 position;
	float radius;
	Vector3 colour;
};

class Renderer : public OGLRenderer	
{
public:
	Renderer(Window &parent);
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
	vector<RenderObject*> renderObjects;
	Light light;
};


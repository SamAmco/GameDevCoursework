#pragma once

#include "Matrix4.h"
#include "Mesh.h"
#include "Shader.h"
#include "../MaterialResource.h"
#include "../TextureResource.h"
#include "../MeshResource.h"

//This class has been slightly adapted to accept the resource wrappers as parameters
//instead of the hard data for textures, mesh's and materials
class RenderObject	{
public:
	RenderObject(void);
	RenderObject(MeshResource*m, MaterialResource*mat);
	~RenderObject(void){}

	Mesh*	GetMesh()	const			{return mesh;}

	Shader* GetShader()		const		{ return shader; }

	void	AddTexture(TextureResource* tex) { textures.push_back(tex->tex); }
	void	ClearTextures() { textures.clear(); }

	void	SetModelMatrix(Matrix4 mat) {modelMatrix = mat;}
	Matrix4 GetModelMatrix()	const	{return modelMatrix;}

	virtual void Update(float msec);

	virtual void Draw() const;

	//virtual void Update(float msec);

	void	AddChild(RenderObject &child) {
		children.push_back(&child);
		child.parent = this;
	}

	Matrix4 GetWorldTransform() const {
		return worldTransform;
	}

	const vector<RenderObject*>& GetChildren() const  {
		return children;
	}

protected:
	Mesh*	mesh;
	Shader*	shader;

	vector<GLuint> textures;

	Matrix4 modelMatrix;
	Matrix4 worldTransform;

	RenderObject*			parent;
	vector<RenderObject*>	children;
};


#include "stdafx.h"
#include "Game.h"

#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>


Game::Game(Renderer& renderer)
	: renderer(renderer)
{
	Mesh* m = MeshManager::getInstance().LoadMesh("monkey.obj");

	shaders = vector<Shader*>(8);
	shaders[0] = ShaderManager::getInstance().LoadShader("BasicVert", "BasicFrag");
	shaders[1] = ShaderManager::getInstance().LoadShader("SinExpandVert", "BasicFrag");//A vertex shader which modulates the scale of objects over time, using a uniform variable.
	shaders[2] = ShaderManager::getInstance().LoadShader("BasicVert", "TexBlendSineFrag");//A fragment shader which blends back and forth between two textures.
	shaders[3] = ShaderManager::getInstance().LoadShader("BasicVert", "BasicFrag", "PosSineGeom");//A geometry shader using a position-based sine wave to move vertices.
	shaders[4] = ShaderManager::getInstance().LoadShader("BasicVert", "ThreeTexBlendFrag");//Perform a non-trivial blend between two textures, perhaps using a third, greyscale texture to determine blend levels.
	shaders[5] = ShaderManager::getInstance().LoadShader("BasicVert", "BasicFrag", "WireframeGeom");//Take in the vertices of the cube, and output new primitives from them (points, lines, or triangles forming new cubes)
	shaders[6] = ShaderManager::getInstance().LoadShader("PhongVert", "PhongFrag");//Calculate per - fragment lighting(using light information accessed from uniform variables)
	shaders[7] = ShaderManager::getInstance().LoadShader("BasicVert", "TransparentWhiteFrag");//Make part of the cube semi-transparent, while still rendering correctly from all orientations
	shaderInd = 0;

	o = RenderObject(m, shaders[shaderInd]);
	o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	o.AddTexture(TextureManager::getInstance().LoadTexture("smiley.png"));
	o.AddTexture(TextureManager::getInstance().LoadTexture("perlin.png"));
	o.AddTexture(TextureManager::getInstance().LoadTexture("noise.png"));
	renderer.AddRenderObject(o);

	lightCol = Vector3(1, 1, 1);
	lightPos = Vector3(100.0f, 100.0f, 0);
	lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));
}

void Game::Update(sf::Event event, float msec)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Right)
		{
			shaderInd = ++shaderInd % shaders.size();
			o.SetShader(shaders[shaderInd]);
		}
	}

	Matrix4 p = Matrix4();
	p.ToIdentity();
	p.SetPositionVector(lightPos);
	lightPos = (Matrix4::Rotation(0.1f * msec, Vector3(0, 1, 0)) * p).GetPositionVector();
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	o.SetModelMatrix(o.GetModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(1, 1, 1)));
}

Game::~Game()
{
}

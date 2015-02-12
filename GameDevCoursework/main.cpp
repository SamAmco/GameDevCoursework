#include "stdafx.h"
#include <GL\glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include "GraphicsCode\Renderer.h"
#include "TextureManager.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// create the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	sf::Window window = sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	Renderer renderer = Renderer();
	window.setVerticalSyncEnabled(true);

	if (glewInit() != GLEW_OK) 
	{	//Try to initialise GLEW
		std::cout << "OGLRenderer::OGLRenderer(): Cannot initialise GLEW!" << std::endl;
		return -1;
	}

	Mesh*	m = Mesh::LoadMeshFile("cube.obj");
	vector<Shader*> shaders = vector<Shader*>(8);
	shaders[0] = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl");
	shaders[1] = new Shader("Shaders/SinExpandVert.glsl", "Shaders/BasicFrag.glsl");//A vertex shader which modulates the scale of objects over time, using a uniform variable.
	shaders[2] = new Shader("Shaders/BasicVert.glsl", "Shaders/TexBlendSineFrag.glsl");//A fragment shader which blends back and forth between two textures.
	shaders[3] = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl", "Shaders/PosSineGeom.glsl");//A geometry shader using a position-based sine wave to move vertices.
	shaders[4] = new Shader("Shaders/BasicVert.glsl", "Shaders/ThreeTexBlendFrag.glsl");//Perform a non-trivial blend between two textures, perhaps using a third, greyscale texture to determine blend levels.
	shaders[5] = new Shader("Shaders/BasicVert.glsl", "Shaders/BasicFrag.glsl", "Shaders/WireframeGeom.glsl");//Take in the vertices of the cube, and output new primitives from them (points, lines, or triangles forming new cubes)
	shaders[6] = new Shader("Shaders/PhongVert.glsl", "Shaders/PhongFrag.glsl");//Calculate per - fragment lighting(using light information accessed from uniform variables)
	shaders[7] = new Shader("Shaders/BasicVert.glsl", "Shaders/TransparentWhiteFrag.glsl");//Make part of the cube semi-transparent, while still rendering correctly from all orientations
	int shaderInd = 0;


	RenderObject o(m, shaders[shaderInd]);
	o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	o.AddTexture(TextureManager::getInstance().LoadTexture("smiley.png"));
	o.AddTexture(TextureManager::getInstance().LoadTexture("perlin.png"));
	o.AddTexture(TextureManager::getInstance().LoadTexture("noise.png"));
	renderer.AddRenderObject(o);		

	Vector3 lightCol = Vector3(1, 1, 1);
	Vector3 lightPos = Vector3(100.0f, 100.0f, 0);
	float lightRad = 3000.0f;

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.SetMainLight(lightCol, lightPos, lightRad);
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	bool running = true;
	bool rightKeyWasDown = false;
	sf::Clock clock;
	while (running)
	{
		float msec = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				running = false;
			else if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					shaderInd = ++shaderInd % shaders.size();
					o.SetShader(shaders[shaderInd]);
				}
			}
		}

		Matrix4 p = Matrix4();
		p.ToIdentity();
		p.SetPositionVector(lightPos);
		lightPos = (Matrix4::Rotation(0.1f * msec, Vector3(0, 1, 0)) * p).GetPositionVector();
		renderer.SetMainLight(lightCol, lightPos, lightRad);
		o.SetModelMatrix(o.GetModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(1, 1, 1)));

		renderer.UpdateScene(msec);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.RenderScene();
		window.display();
	}

	TextureManager::getInstance().UnloadTextures();

	delete m;
	for (unsigned int i = 0; i < shaders.size(); ++i)
		delete shaders[i];

	return 0;
}

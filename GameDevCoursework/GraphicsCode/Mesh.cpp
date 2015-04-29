#include "Mesh.h"
#include <iostream>
#include <vector>

Mesh::Mesh(void)	
{
	//Most objects in OpenGL are represented as 'names' - an unsigned int
	//index, really. They are always generated and destroyed by OpenGL 
	//functions. Most of these functions allow you to generate multiple
	//names at once (the first parameter here is a count).
	glGenVertexArrays(1, &arrayObject);
	
	for(int i = 0; i < MAX_BUFFER; ++i) {
		bufferObject[i] = 0;
	}

	numVertices  = 0;
	type		 = GL_TRIANGLES;

	//Later tutorial stuff
	numIndices    = 0;
	vertices	  = NULL;
	textureCoords = NULL;
	normals		  = NULL;
	tangents	  = NULL;
	indices		  = NULL;
	colours		  = NULL;
}

Mesh::~Mesh(void)	{
	glDeleteVertexArrays(1, &arrayObject);			//Delete our VAO
	glDeleteBuffers(MAX_BUFFER, bufferObject);		//Delete our VBOs

	//Later tutorial stuff
	delete[]vertices;
	delete[]indices;
	delete[]textureCoords;
	delete[]tangents;
	delete[]normals;
	delete[]colours;
}

void Mesh::Draw()	{
	/*
	To render with a mesh in OpenGL, we need to bind all of the buffers
	containing vertex data to the pipeline, and attach them to the
	generic attributes referenced in our vertex shader.
	That's quite a lot of code to set up, but fear not - all of the state
	is cached within our Vertex Array Object, so once that's been set up
	by the BufferData function, all we need to do is bind the VAO and it
	all happens automagically
	*/
	glBindVertexArray(arrayObject);
	//There are two draw functions in OpenGL, depending on whether we're 
	//using indices or not. Both start off taking a primitive type - 
	//triangles, quads, lines, points etc. 

	if(bufferObject[INDEX_BUFFER]) {
		/*
		If we have an index buffer, we tell OpenGL how to parse that
		buffer data (is it bytes/ints/shorts), and how many data
		elements there are. The last parameter should always be 0,
		it's part of the old OpenGL spec.
		*/
		glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
	}
	else{
		/*
		If we don't have indices, we can just use this function.
		Its extra parameters define which is the first vertex
		to draw, and how many vertices past this point to draw.
		*/
		glDrawArrays(type, 0, numVertices);	//Draw the triangle!
	}
	/*
	We don't strictly have to do this, but 'undoing' whatever
	we do to OpenGL in a function generally keeps the pipeline
	from getting incorrect states, or otherwise not doing what
	you want it to do.
	*/
	glBindVertexArray(0);	
}

Mesh* Mesh::GenerateTriangle()	{
	Mesh*m = new Mesh();
	m->numVertices = 3;

	m->vertices		= new Vector3[m->numVertices];
	m->vertices[0]	= Vector3(0.0f,	0.5f,	0.0f);
	m->vertices[1]	= Vector3(0.5f,  -0.5f,	0.0f);
	m->vertices[2]	= Vector3(-0.5f, -0.5f,	0.0f);

	m->textureCoords	= new Vector2[m->numVertices];
	m->textureCoords[0] = Vector2(0.5f,	0.0f);
	m->textureCoords[1] = Vector2(1.0f,	1.0f);
	m->textureCoords[2] = Vector2(0.0f,	1.0f);

	m->colours		= new Vector4[m->numVertices];
	m->colours[0]	= Vector4(1.0f, 0.0f, 0.0f,1.0f); 
	m->colours[1]	= Vector4(0.0f, 1.0f, 0.0f,1.0f);
	m->colours[2]	= Vector4(0.0f, 0.0f, 1.0f,1.0f);

	m->GenerateNormals();
	m->BufferData();

	return m;
}

Mesh* Mesh::GenerateQuad()
{
	Mesh* m = new Mesh();
	
	m-> numVertices = 4;
	m-> type = GL_TRIANGLE_STRIP;

	m->vertices = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m-> numVertices];
	m->colours = new Vector4[m-> numVertices];
	m->normals = new Vector3[m-> numVertices];
	m->tangents = new Vector3[m-> numVertices];

	m-> vertices[0] = Vector3(-1.0f, -1.0f, 0.0f);
	m-> vertices[1] = Vector3(-1.0f, 1.0f, 0.0f);
	m-> vertices[2] = Vector3(1.0f, -1.0f, 0.0f);
	m-> vertices[3] = Vector3(1.0f, 1.0f, 0.0f);
	
	m-> textureCoords[0] = Vector2(0.0f, 1.0f);
	m-> textureCoords[1] = Vector2(0.0f, 0.0f);
	m-> textureCoords[2] = Vector2(1.0f, 1.0f);
	m-> textureCoords[3] = Vector2(1.0f, 0.0f);
	
	for (int i = 0; i < 4; ++i) {
		m-> colours[i] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		m-> normals[i] = Vector3(0.0f, 0.0f, -1.0f);
		m-> tangents[i] = Vector3(1.0f, 0.0f, 0.0f);
	}

	m->BufferData();

	return m;

}

// CSC3224 NCODE  Samuel Amantea-Collins 110148685 
Mesh*	Mesh::LoadMeshFile(const string &filename)
{
	//This code is an adapted version of the obj parser described here:
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
	//It is updated to use safer file reading functions and to extract the 
	//information relevant from the obj file and place it in a Mesh object.

	using namespace std;

	//These will store values read in from the obj file
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<Vector3> temp_vertices;
	vector<Vector2> temp_uvs;
	vector<Vector3> temp_normals;

	//open the obj file stream
	FILE* file;
	errno_t err = fopen_s(&file, filename.c_str(), "r");
	if (err)
	{
		cout << "Impossible to open the file " << filename << "\n";
		return NULL;
	}

	//Loop through the lines
	while (1)
	{
		const int arrSize = 128;
		char lineHeader[arrSize];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, arrSize);
		if (res == EOF)
			break;

		//if it is a vertex:
		if (strcmp(lineHeader, "v") == 0)
		{
			Vector3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//if it is a UV
		else if (strcmp(lineHeader, "vt") == 0)
		{
			Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = 1.0f-uv.y;//This is a small hack to account for the fact that blender assumes a different texture origin
			temp_uvs.push_back(uv);
		}
		//if it is a normal
		else if (strcmp(lineHeader, "vn") == 0)
		{
			Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//if it is an index for a face
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0],
				&normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				cout << "File " << filename << " can't be read.\n";
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	//TODO: The below method of converting this data to a Mesh object is quite 
	//in-efficient, since it duplicates all vertices used more than once,
	//and doesn't take advantage of the vertex indicies in the obj. This may
	//need work in future.

	//Create a Mesh
	Mesh* m = new Mesh();
	m->numVertices = vertexIndices.size();
	m->vertices = new Vector3[m->numVertices];
	m->textureCoords = new Vector2[m->numVertices];
	m->normals = new Vector3[m->numVertices];

	//loop through the faces
	for (unsigned int i = 0; i < vertexIndices.size(); ++i)
	{
		//create a triangle for each with the relevant data and add it to the Mesh
		unsigned int vertexIndex = vertexIndices[i];
		Vector3 vertex = temp_vertices[vertexIndex - 1];
		m->vertices[i] = vertex;

		unsigned int uvIndex = uvIndices[i];
		Vector2 uv = temp_uvs[uvIndex - 1];
		m->textureCoords[i] = uv;

		unsigned int normalIndex = normalIndices[i];
		Vector3 normal = temp_normals[normalIndex - 1];
		m->normals[i] = normal;
	}

	m->BufferData();
	return m;
}
// CSC3224 NCODE BLOCK ENDS

void Mesh::GenerateNormals() 
{
	if (!normals) 
	{
		normals = new Vector3[numVertices];
	}
	for (unsigned int i = 0; i < numVertices; i += 3)
	{
		Vector3 & a = vertices[i];
		Vector3 & b = vertices[i + 1];
		Vector3 & c = vertices[i + 2];

		Vector3 normal = Vector3::Cross(b - a, c - a);
		normal.Normalise();

		normals[i] = normal;
		normals[i + 1] = normal;
		normals[i + 2] = normal;
	}
}


void	Mesh::BufferData()	
{
	/*
		To more efficiently bind and unbind the states required to draw a mesh,
		we can encapsulate them all inside a Vertex Array Object.

		When a VAO is bound, all further changes to vertex buffers and vertex
		attributes are cached inside the VAO, and will be reapplied whenever
		that VAO is later bound again
	*/
	glBindVertexArray(arrayObject);

	/*
	To put some vertex data on the GPU, we must create a buffer object to store it.

	To upload data to a vertex buffer, it must be bound, with a specific 'target',
	which defines what the buffer is to be used for.

	Then, once bound, data can be uploaded using the glBufferData function, which
	takes a pointer to the data to be sent, and the size of that data, as well as
	a usage parameter - this lets OpenGL know how the data will be accessed.

	To turn a vertex buffer into a vertex attribute suitable for sending to a
	vertex shader, the glVertexAttribPointer function must be called. 
	This takes in an attribute 'slot', how many elements each data entry has
	(i.e 2 for a vector2 etc), and what datatype (usually float) it is.
	This will bind the currently bound vertex buffer to that attribute slot.
	To actually enable that attribute slot, the glEnableVertexAttribArray is called.

	Note that we use the value VERTEX_BUFFER for the 'slot' parameter - this is just
	an enum value, that equates to 0. It's common to use enums as indices into arrays
	in this way, as it keeps everything consistent. It's also pretty sensible to always
	bind the same data types to the same attribute slots, it makes life much easier!

	These last two functions, along with the glBindBuffer call, are examples of 
	functionality that is cached in the actual VAO.
	*/

	//Buffer vertex data
	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(VERTEX_BUFFER);

	////Buffer texture data
	if (textureCoords) 
	{
		glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector2), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}

	//buffer colour data
	if (colours)	
	{
		glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector4), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	//buffer normals data
	if (normals)
	{
		glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(Vector3), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(NORMAL_BUFFER);
	}

	//buffer index data
	if (indices)
	{
		glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	//Once we're done with the vertex buffer binding, we can unbind the VAO,
	//ready to reapply later, such as in the Draw function above!
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
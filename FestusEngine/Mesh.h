#pragma once

class MeshLoader;

//Type of vertices that should be loaded
enum VertexType {
	//Position
	P,
	//Position, texture coordinates
	PT,
	//Position, texture coordinates, normals
	PTN,
	//Position, texture coordinates, normals, tangents
	PTNT,

};

//A class that represents a 3D object. Vertex loading is done by an user-defined implementation, and copy of verticies is not kept.
class Mesh {
public:

	//Loads the vertices from a file and fills the openGL buffers. 
	Mesh(const string& filename, VertexType type);


	//Renders the mesh. Set uniforms and shaders before this
	void render();

	//Returns the Vertex Buffer Object
	GLuint getVBO() const { return vbo; }

	//Returns the Vertex Array Object
	GLuint getVAO() const { return vao; }

	//Returns the Index Buffer Object
	GLuint getIBO() const { return ibo; }

	string getFilename() const { return filename; }

	VertexType getVertexType() const { return vertexType; }

private:

	//Vertex buffer object(contains vertices)
	GLuint vbo;

	//Vertex array object(how should those be used)
	GLuint vao;

	//Element array buffer(contains indexes)
	GLuint ibo;

	VertexType vertexType;

	U32 numIndicies;

	string filename;


};
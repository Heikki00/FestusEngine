#include "Mesh.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"


Mesh::Mesh(const string& filename, VertexType type)
{
	this->filename = filename;


	Assimp::Importer importer;

	U32 loadFlags = aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

	if (type == VertexType::PTNT) loadFlags = loadFlags | aiProcess_CalcTangentSpace;

	const aiScene* scene = importer.ReadFile(filename, loadFlags);



	if (!scene) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Failed to load mesh from file: %s\n", filename.c_str());
	}

	const aiMesh* model = scene->mMeshes[0];


	//Generate buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vao);



	//Bind buffers and fill vbo with verticies
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo);



	
	std::vector<U32> indices;
	indices.reserve(model->mNumFaces * 3);
	U32 vertexSize = 0;

	switch (type)
	{
	case P:

		vertexSize = sizeof(Vector3);
		glBufferData(GL_ARRAY_BUFFER, model->mNumVertices * vertexSize, model->mVertices, GL_STATIC_DRAW);
		
		
	 break;
	case PT:


		vertexSize = sizeof(Vector3) * 2;
		glBufferData(GL_ARRAY_BUFFER, model->mNumVertices * vertexSize, model->mVertices, GL_STATIC_DRAW);
	
		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3), model->mNumVertices * sizeof(Vector3), model->mTextureCoords[0]);
		
		

		break;
	case PTN:

		vertexSize = sizeof(Vector3) * 3;
		glBufferData(GL_ARRAY_BUFFER, model->mNumVertices * vertexSize, model->mVertices, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3), model->mNumVertices * sizeof(Vector3), model->mTextureCoords[0]);

		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3) * 2, model->mNumVertices * sizeof(Vector3), model->mNormals);

		break;
	case PTNT:
		vertexSize = sizeof(Vector3) * 4;
		glBufferData(GL_ARRAY_BUFFER, model->mNumVertices * vertexSize, model->mVertices, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3), model->mNumVertices * sizeof(Vector3), model->mTextureCoords[0]);

		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3) * 2, model->mNumVertices * sizeof(Vector3), model->mNormals);
		
		glBufferSubData(GL_ARRAY_BUFFER, model->mNumVertices * sizeof(Vector3) * 3, model->mNumVertices * sizeof(Vector3), model->mTangents);
		break;
	}

	


	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		const aiFace& face = model->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
		
	}
	

//LOAD
		this->numIndicies = indices.size();

		

		glBindVertexArray(vao);
		
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		if (vertexSize > sizeof(Vector3)) {
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(Vector3) * model->mNumVertices));
			glEnableVertexAttribArray(1);
			
		}

		if (vertexSize > sizeof(Vector3)* 2) {
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(Vector3) * model->mNumVertices * 2));
			glEnableVertexAttribArray(2);
			
		}

		if (vertexSize > sizeof(Vector3)  * 3) {
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(Vector3) * model->mNumVertices * 3));
			glEnableVertexAttribArray(3);
		}

		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(U32), &indices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	


}

void Mesh::render()
{
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glDrawElements(GL_TRIANGLES, numIndicies, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


}


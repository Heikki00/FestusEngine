#include "Canvas.h"
#include "Material.h"
#include "Shader.h"
#include "Mesh.h"

Canvas::Canvas()
{
	m = resourceManager->fetchMesh("Resources/Meshes/Canvas.obj", VertexType::PT);
}

Canvas::~Canvas()
{
	resourceManager->freeMesh(m);
}

void Canvas::render(Shader* s)
{
	s->bind();

	MappedValues map;
	Transform t;
	s->updateUniforms(dynamic_cast<Material*>(&map), t);
	m->render();
}

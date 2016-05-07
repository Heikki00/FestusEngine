#include "MeshRenderer.h"
#include "ResourceManager.h"


COMPONENTREGISTER(MeshRenderer)


MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : GameComponent(), mesh(mesh), material(material)
{ 
	type = TypeID<MeshRenderer>::getType();

	


}

MeshRenderer::~MeshRenderer()
{
	resourceManager->freeMesh(mesh);
	delete material;
}

void MeshRenderer::render(U32 renderType)
{
	
	if(!material->render(renderType, getParent())) return;
	
	
	mesh->render();
	
}

Mesh* MeshRenderer::getMesh() const
{
	return mesh;
}

void MeshRenderer::setMesh(Mesh* val)
{
	resourceManager->freeMesh(mesh);
	mesh = val;
}

Material* MeshRenderer::getMaterial() const
{
	return material;
}

void MeshRenderer::setMaterial(Material* val)
{
	material = val;
}

bool MeshRenderer::getEnabled() const
{
	return enabled;
}

void MeshRenderer::setEnabled(bool val)
{
	enabled = val;
}

MappedValues* MeshRenderer::save()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void MeshRenderer::load(const MappedValues& map)
{
	throw std::logic_error("The method or operation is not implemented.");
}


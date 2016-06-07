#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "BasicMaterial.h"


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
	MappedValues* m = new MappedValues;
	m->setString("type", "MeshRenderer");
	m->setString("filename", mesh->getFilename());
	m->setU32("vertType", (U32)mesh->getVertexType());
	m->setString("material", material->getFilename());
	if(materialSaving)	material->save();
	return m;
}

void MeshRenderer::load(const MappedValues& map)
{
	type = TypeID<MeshRenderer>::getType();
	
	mesh = resourceManager->fetchMesh(map.getString("filename"), (VertexType)map.getU32("vertType"));

	material = new BasicMaterial(map.getString("material"));

}


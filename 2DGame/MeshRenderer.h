#pragma once
#include "Mesh.h"
#include "Material.h"
#include "GameComponent.h"



class MeshRenderer : public GameComponent {
public:
	MeshRenderer(Mesh* mesh, Material* material);

	~MeshRenderer();

	void render(U32 renderType) override;




	Mesh* getMesh() const;
	void setMesh(Mesh* val);

	Material* getMaterial() const;
	void setMaterial(Material* val);

	//Returns a value indicating if the renderer is  enabled
	bool getEnabled() const;
	void setEnabled(bool val);

	//Returns a value indicating if the material will be saved on save().
	bool getMaterialSaving() const { return materialSaving; }
	void setMaterialSaving(bool b) { materialSaving = b; }

	virtual MappedValues* save() override;

	virtual void load(const MappedValues& map) override;

	COMPONENTLOADCONSTRUCTOR(MeshRenderer)

private:


	Mesh* mesh;
	Material* material;
	bool enabled, materialSaving;










};

#pragma once
#include "Material.h"

class Shader;
class Texture;
class BasicMaterial : public Material {

public:


	BasicMaterial(const string& filename, Shader* s);


	~BasicMaterial();


	virtual bool render(U32 renderType, GameObject* go) override;



private:


	Shader* shader;

};


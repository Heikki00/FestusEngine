#pragma once
#include "BaseLight.h"

//Class that represent light that has direction but not position. Used for things like the sun
class DirectionalLight : public BaseLight{
public:

	DirectionalLight(const Vector3& color, float intensity);

	virtual ~DirectionalLight() = default;

	virtual void setUniform(const string& uniform, Shader* shader) override;

	Vector3 getDirection() const;

	virtual MappedValues* save() override;


	virtual void load(const MappedValues& map) override;

	
	COMPONENTLOADCONSTRUCTOR(DirectionalLight)
};
#pragma once
#include "UniformStruct.h"


//Class that does not represent actual light, but serves as base for every other light.
//Contains intensity and color
class BaseLight : public UniformStruct, public GameComponent{
public:


	BaseLight(const Vector3& color, float intensity);

	virtual ~BaseLight() = default;

	virtual void free() override;

	Vector3 getColor() const;
	void setColor(Vector3 val);


	float getIntensity() const;
	void setIntensity(float val);

	virtual void setUniform(const string& uniform, Shader* shader) override;

	virtual MappedValues* save() override;

	COMPONENTLOADCONSTRUCTOR(BaseLight)

	virtual void load(const MappedValues& map) override;

private:

	Vector3 color;
	float intensity;
	


};


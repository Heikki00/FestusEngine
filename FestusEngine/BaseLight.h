#pragma once
#include "UniformStruct.h"


//Class that does not represent actual light, but serves as base for every other light.
//Contains intensity and color
class BaseLight : public UniformStruct, public GameComponent{
public:


	BaseLight(const Vector3& color, float intensity);

	BaseLight();

	virtual ~BaseLight() = default;

	virtual void free() override;

	virtual void update() override;
	
	//Returns true if the light is enabled(requiers its scene to be active)
	bool isEnabled() const { return enabled && intEnabled; }

	void setEnabled(bool e) { enabled = e; }

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
	bool enabled, intEnabled;


};


#pragma once
#include "BaseLight.h"


class PointLight : public BaseLight{
public:
	PointLight(const Vector3& color, float intensity, float range);

	virtual void setUniform(const string& uniform, Shader* shader) override;





	float getRange() const;
	void setRange(float val);

	virtual MappedValues* save() override;

	virtual void load(const MappedValues& map) override;

	COMPONENTLOADCONSTRUCTOR(PointLight)

private:

	float range;

};
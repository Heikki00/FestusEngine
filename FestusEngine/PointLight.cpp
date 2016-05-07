#include "PointLight.h"
#include "Shader.h"

COMPONENTREGISTER(PointLight)

PointLight::PointLight(const Vector3& color, float intensity, float range) : BaseLight(color, intensity)
{
	type = TypeID<PointLight>::getType();
	this->range = range;

}

void PointLight::setUniform(const string& uniform, Shader* shader)
{
	BaseLight::setUniform(uniform + ".base", shader);

	shader->setUniformStructMember(uniform + ".positon", getTransform().getWorldPosition());

	shader->setUniformStructMember(uniform + ".range", range);

}

float PointLight::getRange() const
{
	return range;
}

void PointLight::setRange(float val)
{
	range = val;
}

MappedValues* PointLight::save()
{
	MappedValues* res = BaseLight::save();

	res->setString("type", "PointLight");

	res->setFloat("range", range);

	return res;
}

void PointLight::load(const MappedValues& map)
{
	BaseLight::load(map);

	type = TypeID<PointLight>::getType();

	range = map.getFloat("range");
}

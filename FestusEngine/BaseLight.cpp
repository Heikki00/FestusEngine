#pragma once
#include "BaseLight.h"
#include "Shader.h"

COMPONENTREGISTER(BaseLight)

BaseLight::BaseLight(const Vector3& color, float intensity) : GameComponent()
{
	renderingEngine->addLight(this);
	type = TypeID<BaseLight>::getType();

	this->color = color;
	this->intensity = intensity;
}

void BaseLight::free()
{
	renderingEngine->removeLight(this);
}

Vector3 BaseLight::getColor() const
{
	return color;
}

void BaseLight::setColor(Vector3 val)
{
	color = val;
}

float BaseLight::getIntensity() const
{
	return intensity;
}

void BaseLight::setIntensity(float val)
{
	intensity = val;
}

void BaseLight::setUniform(const string& uniform, Shader* shader)
{
	shader->setUniformStructMember(uniform + ".color", color);
	shader->setUniformStructMember(uniform + ".intensity", intensity);

}

MappedValues* BaseLight::save()
{
	MappedValues* res = nullptr;

	res->setString("type", "BaseLight");

	res->setVector3("color", color);

	res->setFloat("intensity", intensity);

	return res;

}

void BaseLight::load(const MappedValues& map)
{
	type = TypeID<BaseLight>::getType();

	color = map.getVector3("color");

	intensity = map.getFloat("intensity");

}


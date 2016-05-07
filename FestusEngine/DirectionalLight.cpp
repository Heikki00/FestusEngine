#pragma once
#include "DirectionalLight.h"
#include "Shader.h"

COMPONENTREGISTER(DirectionalLight)

DirectionalLight::DirectionalLight(const Vector3& color, float intensity) : BaseLight(color, intensity)
{
	
		type = TypeID<DirectionalLight>::getType();
	
}

void DirectionalLight::setUniform(const string& uniform, Shader* shader)
{
	BaseLight::setUniform(uniform + ".base", shader);
	shader->setUniformStructMember(uniform + ".direction", getParent()->getTransform().getWorldForward());
	
}

Vector3 DirectionalLight::getDirection() const
{
	return getParent()->getTransform().getWorldForward();
}

MappedValues* DirectionalLight::save()
{
	MappedValues* res = BaseLight::save();


	res->setString("type", "DirectionalLight");

	return res;
}

void DirectionalLight::load(const MappedValues& map)
{
	BaseLight::load(map);
	
	type = TypeID<DirectionalLight>::getType();

	
}


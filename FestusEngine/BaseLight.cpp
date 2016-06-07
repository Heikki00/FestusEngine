#pragma once
#include "BaseLight.h"
#include "Shader.h"
#include "Game.h"

COMPONENTREGISTER(BaseLight)

BaseLight::BaseLight(const Vector3& color, float intensity) : GameComponent()
{
	
	type = TypeID<BaseLight>::getType();
	renderingEngine->addLight(this);
	this->color = color;
	this->intensity = intensity;
	enabled = true;
	intEnabled = false;

}

BaseLight::BaseLight()
{
	renderingEngine->addLight(this);
	
	type = TypeID<BaseLight>::getType();
	this->color = Vector3(1, 1, 1);
	this->intensity = 1.f;
	enabled = true;
	intEnabled = false;
}

void BaseLight::free()
{
	renderingEngine->removeLight(this);
}

//TODO: optimize, maybe an event when the scene changes?
void BaseLight::update()
{
	if (getParent()->getRoot() == game->getActiveScene()->getRoot()) intEnabled = true;
	else intEnabled = false;
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
	MappedValues* res = new MappedValues;

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


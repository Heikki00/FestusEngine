#pragma once
#include "Camera.h"
#include "RenderingEngine.h"

COMPONENTREGISTER(Camera)

Camera::Camera(F32 fov, F32 aspect, F32 zNear, F32 zFar) : GameComponent()
{
	perspective = Math::perspectiveMatrix(fov, aspect, zNear, zFar);
	type = TypeID<Camera>::getType();

}


Camera::Camera(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far)
{
	perspective = Math::orthographicMatrix(left, right, top, bottom, near, far);
	type = TypeID<Camera>::getType();
}

void Camera::setPerspective(const Matrix4& mat)
{
	perspective = mat;
}

Matrix4 Camera::getVP()
{
	return perspective * getTransform().getTransform().inverse();
}

Matrix4 Camera::getV()
{
	return getTransform().getTransform().inverse();
}

Matrix4 Camera::getP()
{
	return perspective;
}

MappedValues* Camera::save()
{
	MappedValues* res = new MappedValues;


	res->setString("type", "Camera");

	res->setMatrix4("perspective", perspective);

	return res;

}

void Camera::load(const MappedValues& map)
{
	type = TypeID<Camera>::getType();
	perspective = map.getMatrix4("perspective");


}


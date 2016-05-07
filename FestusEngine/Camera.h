#pragma once
#include "GameComponent.h"
#include "Input.h"

class Camera : public GameComponent {
public:

	Camera(F32 fov, F32 aspect, F32 zNear, F32 zFar);

	Camera(F32 left, F32 right, F32 top, F32 bottom, F32 near, F32 far);

	void setPerspective(const Matrix4& mat);

	Matrix4 getVP();

	Matrix4 getV();

	Matrix4 getP();

	virtual MappedValues* save() override;

	virtual void load(const MappedValues& map) override;

	COMPONENTLOADCONSTRUCTOR(Camera)


private:

	Matrix4 perspective;




};
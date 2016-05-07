#pragma once
#include "GameComponent.h"



class TilePhysics : public GameComponent {
public:
	TilePhysics(F32 size, F32 mass, F32 friction, F32 bounciness);



	virtual void update() override;

	F32 getSize() const;



	F32 getMass() const { return mass; }
	void setMass(F32 val) { mass = val; }

	F32 getFriction() const { return friction; }
	void setFriction(F32 val) { friction = val; }

	F32 getBounciness() const { return bounciness; }
	void setBounciness(F32 val) { bounciness = val; }

	Vector2 getMomentum() const { return momentum; }
	void setMomentum(Vector2 val) { momentum = val; }

	Vector2 getAcceleration() const { return acceleration; }
	void setAcceleration(Vector2 val) { acceleration = val; }


private:
	F32 size;
	F32 mass, friction, bounciness;
	Vector2 momentum, acceleration;



};
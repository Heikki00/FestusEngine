#pragma once
#include "..\FestusEngine\GameComponent.h"
#include "BasicMaterial.h"


enum class ColorTile : U32{
	RED = 0u,
	YELLOW,
	GREEN, // NOT REALLY
	ORANGE,
	BLUE,
	PURPLE,
	PINK
};

enum class Scent {
	NONE = 0,
	ORANGE,
	LEMON
};

class TileRenderer;

class Arena : public GameComponent {
public:

	virtual void init() override;

	virtual void free() override;

	virtual void update() override;

	virtual void render(U32 renderType) override;

	
	void setDimensions(U32 width, U32 height);

	void setTile(U32 x, U32 y, ColorTile tile);


	U32 getWidth() const { return width; }

	U32 getHeight() const { return height; }


	virtual MappedValues* save() override;

	virtual void load(const MappedValues&) override;

	COMPONENTLOADCONSTRUCTOR(Arena);

private:

	Vector3 getColor(U32 x, U32 y);

	void move(Vector2 start, Vector2 end);


	U32 width, height;

	std::vector<std::vector<ColorTile>> map;

	Scent scent;

	Vector2 location;

	Mesh* mesh;

	BasicMaterial* material;
	BasicMaterial* playerMaterial;
};
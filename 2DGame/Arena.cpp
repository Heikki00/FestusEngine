#include "Arena.h"

COMPONENTREGISTER(Arena)


void Arena::init()
{
	type = TypeID<Arena>::getType();

	

	mesh = resourceManager->fetchMesh("Resources/Meshes/Square.obj", VertexType::PT);

	material = new BasicMaterial("Resources/Materials/TileMaterial.mat", resourceManager->fetchShader("Resources/Shaders/TileShader.glsl"));


	playerMaterial = new BasicMaterial("Resources/Materials/PlayerMaterial.mat", resourceManager->fetchShader("Resources/Shaders/Basic2D.glsl"));

	playerMaterial->setTexture("diffuse", resourceManager->loadTexture(new Texture("Resources/Textures/Player.png", GL_TEXTURE_2D, GL_NONE, GL_RGBA8, GL_UNSIGNED_BYTE, GL_NEAREST)));

	
	width = height = 0;


}




void Arena::free()
{
	delete playerMaterial;
	delete material;
	resourceManager->freeMesh(mesh);
}

void Arena::update()
{
	
	if (input->wasKeyPressed(SDLK_UP)) {
	
			move(location, Vector2(location.x, location.y + 1));


	}

	if (input->wasKeyPressed(SDLK_DOWN)) {
		move(location, Vector2(location.x, location.y - 1));

	}

	if (input->wasKeyPressed(SDLK_LEFT)) {
		move(location, Vector2(location.x - 1, location.y));

	}

	if (input->wasKeyPressed(SDLK_RIGHT)) {
		move(location, Vector2(location.x + 1, location.y));

	}


	GLenum err = glGetError();

	if (err != GL_NO_ERROR) {
		std::cout << "?!\n";
	}

}


void Arena::render(U32 renderType)
{
	for (U32 x = 0; x < width; ++x) {
		for (U32 y = 0; y < height; ++y) {
			material->setVector3("tileColor", getColor(x, y));
			getTransform().setPosition(Vector3((F32)x + 0.5f, (F32)y + 0.5f, -10.f));
			playerMaterial->render(renderType, getParent());
			mesh->render();
		
		}




	}

	getTransform().setPosition(Vector3(location.x, location.y, -1.f));
	playerMaterial->render(renderType, getParent());
	mesh->render();


}

void Arena::setDimensions(U32 width, U32 height)
{

	this->width = width;
	this->height = height;
	//Resize the vector that contains columns
	map.resize(width);

	//Resize all vectors that contain rows
	for (auto& a : map) {
		
		a.resize(height);
	}
	


}

void Arena::setTile(U32 x, U32 y, ColorTile tile)
{
	
	map[x][y] = tile;

	
}



void Arena::move(Vector2 start, Vector2 end)
{
	
	if (end.x < 0 || end.x >= width) return;

	if (end.y < 0 || end.y >= height) return;



	if (map[end.x][end.y] == ColorTile::RED) return;

	if (map[end.x][end.y] == ColorTile::PURPLE) {

		move(start, start + (end - start) * 2);
		scent = Scent::LEMON;
		return;
	}



	if (map[end.x][end.y] == ColorTile::ORANGE) {
		scent = Scent::ORANGE;
	}

	if (map[end.x][end.y] == ColorTile::YELLOW) {
		//HP SYSTEM
		return;
	}


	if (map[end.x][end.y] == ColorTile::BLUE) {
		if (scent == Scent::ORANGE) return;
		
		try {
			if (map.at(end.x + 1).at(end.y) == ColorTile::YELLOW) {
				//HP
				return;
			}
		} catch(...){}

		try {
			if (map.at(end.x - 1).at(end.y) == ColorTile::YELLOW) {
				//HP
				return;
			}
		}
		catch (...) {}

		try {
			if (map.at(end.x).at(end.y + 1) == ColorTile::YELLOW) {
				//HP
				return;
			}
		}
		catch (...) {}

		try {
			if (map.at(end.x + 1).at(end.y - 1) == ColorTile::YELLOW) {
				//HP
				return;
			}
		}
		catch (...) {}

	}
	


	location = end;








}


Vector3 Arena::getColor(U32 x, U32 y)
{
	switch (map[x][y])
	{
	case ColorTile::RED: return Vector3(1, 0, 0);
		break;
	case ColorTile::YELLOW: return Vector3(1, 1, 0);
		break;
	case ColorTile::GREEN: return Vector3(0, 1, 0);
		break;
	case ColorTile::ORANGE: return Vector3(1, 0.5f, 0);
		break;
	case ColorTile::BLUE: return Vector3(0, 0, 1);
		break;
	case ColorTile::PURPLE: return Vector3(1, 0, 0.5f);
		break;
	case ColorTile::PINK: return Vector3(1, 0, 1);
		break;
	default: return Vector3(1, 1, 1);
		break;
	}
}

MappedValues* Arena::save()
{
	MappedValues* m = new MappedValues;
	m->setString("type", "Arena");

	m->setU32("width", width);
	m->setU32("height", height);

	for (U32 x = 0; x < width; ++x)
		for (U32 y = 0; y < height; ++y) {
		
			m->setU32("TILE" + std::to_string(x) + "x" + std::to_string(y), (U32)map.at(x).at(y));

		
		
		}


	m->setU32("scent", (U32)scent);

	m->setVector2("location", location);

	return m;

}

void Arena::load(const MappedValues& m)
{


	setDimensions(m.getU32("width"), m.getU32("height"));


	for (U32 x = 0; x < width; ++x)
		for (U32 y = 0; y < height; ++y) {
			setTile(x, y, (ColorTile)m.getU32("TILE" + std::to_string(x) + "x" + std::to_string(y)));

		}


	location = m.getVector2("location");

	scent = (Scent)m.getU32("scent");

}


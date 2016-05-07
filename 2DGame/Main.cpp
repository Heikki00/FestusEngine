//#include "vld.h"

#include "Game.h"
#include "CoreEngine.h"
#include "Shader.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Texture.h"
#include "Material.h"
#include "BasicMaterial.h"
#include "TestGame.h"
#undef main

#include "Input.h"

int main(int argc, char** argv) {
	CoreEngine e;


	e.init(800, 640, "FestusEngine", new TestGame);


	e.run();

	e.free();


	return 0;
}
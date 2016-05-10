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
	/*glFrontFace(GL_CW);
	Shader* s = new Shader("Resources/Shaders/TestShader.glsl");

	Mesh* m = new Mesh("Resources/Meshes/Square.obj", VertexType::P);

	while (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		s->bind();

		m->render();

		window->updateEvents();

		if (window->isClosed()) break;

		window->swapBuffers();

	}
*/

	e.free();


	return 0;
}
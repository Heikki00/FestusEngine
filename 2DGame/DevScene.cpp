#include "DevScene.h"
#include "GameRenderLayer.h"
#include "GUIRenderLayer.h"
#include "FreeMove.h"
#include "Arena.h"


DevScene::DevScene()
{
	type = TypeID<DevScene>::getType();
}

DevScene::~DevScene()
{
	delete root;
}

void DevScene::init()
{
	root = new GameObject("ROOT");

	selected = ColorTile::RED;


	GameObject* cam = new GameObject("Camera");
	float as = (float)window->getWidth() / (float)window->getHeight();
	cam->addComponent(new Camera(0.f , 6.f , 4.f, 0.f, 100.f, -100.f));
	gui->setActiveContext("DevScene");

	gui->setLayout("DevLayout");

	
	gui->getWindow("DefaultWindow/ChoiceWindow/RedRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::RED;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/PinkRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::PINK;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/BlueRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::BLUE;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/PurpleRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::PURPLE;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/OrangeRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::ORANGE;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/YellowRad")->subscribeEvent("SelectStateChanged", [&](const CEGUI::EventArgs & args) -> bool {
		CEGUI::Window* win = static_cast<const CEGUI::WindowEventArgs&>(args).window;
		if (win == static_cast<CEGUI::RadioButton*>(win)->getSelectedButtonInGroup()) {
			selected = ColorTile::YELLOW;
		}
		return true;
	});

	gui->getWindow("DefaultWindow/ChoiceWindow/CameraSlider")->subscribeEvent(CEGUI::Slider::EventValueChanged, [&](const CEGUI::EventArgs& args) -> bool{
		CEGUI::Slider* slider = (CEGUI::Slider*)static_cast<const CEGUI::WindowEventArgs&>(args).window;
		
		gui->getWindow("DefaultWindow/ChoiceWindow/CameraEditbox")->setText(std::to_string(slider->getCurrentValue()));
	
		return true;
	});


	gui->getWindow("DefaultWindow/ChoiceWindow/CameraEditbox")->subscribeEvent(CEGUI::Window::EventTextChanged, [&](const CEGUI::EventArgs & args) -> bool {
	
		CEGUI::Editbox* box = (CEGUI::Editbox*)static_cast<const CEGUI::WindowEventArgs&>(args).window;
		try {
			F32 val = std::stof(string(box->getText().c_str()));

			static_cast<Camera*>(root->getChildByName("Camera")->getComponentOfType(TypeID<Camera>::getType()))->setPerspective(Math::orthographicMatrix(0.f, 3.f + val, 1 + val, 0.f, 100.f, -100.f));
		}
		catch(...){}
		return true;
	});

	GameObject* arenaObj = new GameObject("ARENA");

	Arena* arena = new Arena();
	
	arenaObj->addComponent(arena);

	
	arena->setDimensions(6, 4);

	arena->setTile(1, 1, ColorTile::RED);

	arena->setTile(1, 2, ColorTile::PURPLE);

	arena->setTile(3, 0, ColorTile::YELLOW);

	arena->setTile(4, 0, ColorTile::BLUE);

	arena->setTile(5, 0, ColorTile::BLUE);

	arena->setTile(3,3, ColorTile::ORANGE);

	root->addChild(arenaObj);
	root->addChild(cam);
}

void DevScene::update()
{

	Vector2 pos = input->getMouseLocation();

	if (input->wasMouseButtonPressed(SDL_BUTTON_LEFT) && !gui->getWindow("DefaultWindow/ChoiceWindow")->getClipRect(true).isPointInRect(CEGUI::Vector2f(pos.x, pos.y))) {
		

		


		pos.y *= -1.f;
		pos.y += window->getHeight();
		
		Arena* ar = (Arena*)root->getChildByName("ARENA")->getComponentOfType(TypeID<Arena>::getType());

		F32 width = ar->getWidth();

		F32 height = ar->getHeight();

		ar->setTile(pos.x / ((F32)window->getWidth() / width), pos.y / ((F32)window->getHeight() / height), selected);
		

	
	}


	root->updateAll();

	
}

void DevScene::render()
{
	renderingEngine->render(root);
}

void DevScene::activate()
{
	gui->setActiveContext("DevScene");
	input->captureMouse(false);
	renderingEngine->addLayer(new GameRenderLayer());

	renderingEngine->setCamera(static_cast<Camera*>(root->getChildByName("Camera")->getComponentByIndex(0)));
	renderingEngine->disableGUI();
}

void DevScene::deactivate()
{
	renderingEngine->removeLayer(0);
	renderingEngine->enableGUI();
}

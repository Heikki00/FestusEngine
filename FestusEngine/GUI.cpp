#pragma once
#include "GUI.h"



GUI::GUI()
{
	//TODO: put this in config file?
	resourceDirectory = "Resources/GUI";

	renderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();
	
	
	CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
	rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
	rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
	rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
	rp->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
	rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");


	

	CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");


	

	setActiveContext("Default");

	root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");

	activeContext->setRootWindow(root);



}

GUI::~GUI()
{

	CEGUI::System::getSingleton().destroy();

}

void GUI::render()
{
	renderer->beginRendering();

	activeContext->draw();

	renderer->endRendering();
	glDisable(GL_SCISSOR_TEST);
	
}

void GUI::setActiveContext(const string& context)
{
	activeContext = contexts[context];

	if (!activeContext) {
		activeContext = &CEGUI::System::getSingleton().createGUIContext(renderer->getDefaultRenderTarget());
		contexts[context] = activeContext;
		
		activeContext->setRootWindow(CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root"));
		
	}
	root = activeContext->getRootWindow();


}

void GUI::setFont(const string& font)
{
	CEGUI::FontManager::getSingleton().createFromFile(font + ".font");
	activeContext->setDefaultFont(font);
}

void GUI::loadScheme(const string& name)
{
	CEGUI::SchemeManager::getSingleton().createFromFile(name + ".scheme");

	

}








void GUI::setLayout(const string& name)
{
	root->addChild(CEGUI::WindowManager::getSingleton().loadLayoutFromFile(name.find(".layout") == -1 ? name + ".layout" : name));
}

CEGUI::Window* GUI::addWindow(const string& type, const string& name, const Vector4& relSize, const Vector4& pixelOffsets /*= Vector4(0)*/)
{
	CEGUI::Window* win = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	win->setPosition(CEGUI::UVector2(CEGUI::UDim(relSize.x, pixelOffsets.x), CEGUI::UDim(relSize.y, pixelOffsets.y)));
	win->setSize(CEGUI::USize(CEGUI::UDim(relSize.z, pixelOffsets.z), CEGUI::UDim(relSize.w, pixelOffsets.w)));
	root->addChild(win);


	//TODO: Exception handling


	return win;
}






CEGUI::Window* GUI::getWindow(const string& name)
{
	CEGUI::Window* w = nullptr;
	try
	{
		w = root->getChild(name);
	}
	catch (const CEGUI::UnknownObjectException& e)
	{
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to retrieve nonexciting UI element %s\n", name.c_str());
	}

	return w;
}

CEGUI::GUIContext* GUI::getActiveContext()
{
	return activeContext;
}

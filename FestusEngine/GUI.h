#pragma once


class GUI {
public:


	GUI();

	~GUI();

	void render();

	

	void setActiveContext(const string& context);

	void setFont(const string& font);

	void loadScheme(const string& name);

	//Do nat add .layout
	void setLayout(const string& name);

	CEGUI::Window* addWindow(const string& type, const string& name, const Vector4& relSize, const Vector4& pixelOffsets = Vector4(0));

	CEGUI::Window* getWindow(const string& name);


	CEGUI::GUIContext* getActiveContext();

	

private:

	CEGUI::OpenGL3Renderer* renderer;
	string resourceDirectory;

	std::map<string, CEGUI::GUIContext*> contexts;
	CEGUI::Window* root;
	CEGUI::GUIContext* activeContext;

};


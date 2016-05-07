#pragma once

class GameObject;
class GameComponent;




struct ObjectSaveData {
	string name;

	std::vector<MappedValues*> componentData;

	std::vector<ObjectSaveData> childSaveData;

};


typedef GameComponent* (*LoadInstanceFunction)();

class SaveManager {
public:

	SaveManager();


	void save(GameObject* root);


	void setSaveFile(const string& savefile);


	static void registerLoad(const string& name, LoadInstanceFunction function);

private:
	string savefile;

};


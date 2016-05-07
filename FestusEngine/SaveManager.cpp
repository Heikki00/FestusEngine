#include "SaveManager.h"

std::map<string, LoadInstanceFunction> getLoadFunctions() {
	static std::map<string, LoadInstanceFunction> map;
	return map;
}






//TODO: Put the default into a config file?
SaveManager::SaveManager()
{
	this->savefile = "Resources/Files/DefaultSave.save";
}

void SaveManager::save(GameObject* root)
{
	ObjectSaveData data = root->save();

	Json::Value rootVal;

	rootVal["NAME"] = data.name;

	Json::StyledWriter writer;
	std::string output = writer.write(rootVal);

	std::cout << rootVal << std::endl;



}

void SaveManager::setSaveFile(const string& savefile)
{
	this->savefile = savefile;
}



void SaveManager::registerLoad(const string& name, LoadInstanceFunction function)
{
	

	getLoadFunctions()[name] = function;

}


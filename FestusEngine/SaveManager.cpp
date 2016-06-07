#include "SaveManager.h"

std::map<string, LoadInstanceFunction>& getLoadFunctions() {
	static std::map<string, LoadInstanceFunction> map;
	return map;
}






//TODO: Put the default into a config file?
SaveManager::SaveManager()
{
	this->savefile = "Resources/Files/DefaultSave.save";
}


GameObject* loadRecursive(Json::Value& root) {
	GameObject* g = new GameObject(root["NAME"].asString());
	

	
	fileManager->fromJson(root["TRANSFORM"], &g->getTransform());

	

	Json::Value components = root["COMPONENTS"];
	MappedValues* m = new MappedValues;
	for (auto i = components.begin(); i != components.end() && !components.isNull(); i++) {
		
		m->clear();
		m->fromJson(*i);
	
		getLoadFunctions()[m->getString("type")](g, *m);
		
	}
	delete m;
	Json::Value children = root["CHILDREN"];

	for (auto i = children.begin(); i != children.end(); i++) {
		g->addChild(loadRecursive(*i));
	}


	return g;
}



GameObject* SaveManager::load(const std::string& filename)
{
	std::string src = fileManager->getContents(filename);


	Json::Reader reader;

	Json::Value root;

	reader.parse(src, root);

	GameObject* g = loadRecursive(root);


	
	Json::Value children = root["CHILDREN"];

	


	return g;

}

Json::Value traverse(ObjectSaveData* data) {

	Json::Value val, components, children, *temp;

	temp = fileManager->toJson(data->transform);
	val["TRANSFORM"] = *temp;
	val["NAME"] = *data->name;
	delete temp;

	for (U32 i = 0; i < data->componentData.size(); ++i) {
		temp = data->componentData[i]->toJson();
		components.append(*temp);
		delete temp;
	}
	val["COMPONENTS"] = components;

	for (U32 i = 0; i < data->childSaveData.size(); i++) {
		children.append(traverse(&data->childSaveData[i]));
	}

	val["CHILDREN"] = children;

	return val;
	





}





void SaveManager::save(GameObject* root)
{
	ObjectSaveData data = root->save();

	

	Json::Value val = traverse(&data);




	string res = Json::StyledWriter().write(val);

	fileManager->write(savefile, res);



}

void SaveManager::setSaveFile(const string& savefile)
{
	this->savefile = savefile;
}



void SaveManager::registerLoad(const string& name, LoadInstanceFunction function)
{
	
	getLoadFunctions()[name] = function;

	
}


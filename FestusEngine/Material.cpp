#include "Material.h"

Material::Material(const string& filename)
{
	this->filename = filename;

	if (fileManager->fileExists(filename)) {


		load();
	}
	else {
		fileManager->write(filename, "");
	}
}

void Material::save()
{
	Json::Value* val = toJson();
	fileManager->write(filename, Json::StyledWriter().write(*val));
	delete val;
}

string Material::getFilename()
{
	return filename;
}

void Material::load()
{

	Json::Value* v = fileManager->parseJson(fileManager->getContents(filename));
	fromJson(*v);
	delete v;



}

 
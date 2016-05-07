#include "Material.h"

Material::Material(const string& filename)
{
	this->filename = filename;

	if (fileManager->fileExists(filename)) {


		load();
	}
}

void Material::save()
{
	fileManager->write(filename, fileManager->toJson(this));
}

void Material::load()
{
	MappedValues* m = fileManager->fromJson(fileManager->getContents(filename));

	replaceValues(m);


}

 
#pragma once
#include "MappedValues.h"
#include "ResourceManager.h"
#include "Texture.h"









MappedValues::~MappedValues()
{
	for (auto& t : textures) {
		resourceManager->freeTexture(t.second);
	}

	
}

void MappedValues::setVector2(const string& name, const Vector2& val)
{
	vector2s[name] = val;
}

void MappedValues::setVector3(const string& name, const Vector3& val)
{
	vector3s[name] = val;
}

void MappedValues::setVector4(const string& name, const Vector4& val)
{
	vector4s[name] = val;
}

void MappedValues::setFloat(const string& name, F32 val)
{
	floats[name] = val;
}

void MappedValues::setI32(const string& name, I32 val)
{
	ints[name] = val;
}

void MappedValues::setU32(const string& name, U32 val)
{
	uints[name] = val;
}

void MappedValues::setTexture(const string& name, Texture* val)
{
	textures[name] = val;
}

void MappedValues::setPointer(const string& name, void* val)
{
	pointers[name] = val;
}

void MappedValues::setUniformStruct(const string& name, UniformStruct* val)
{
	uniformStructs[name] = val;
}

void MappedValues::setMatrix4(const string& name, const Matrix4& val)
{
	matrix4s[name] = val;
}

void MappedValues::setMatrix3(const string& name, const Matrix3& val)
{
	matrix3s[name] = val;
}

void MappedValues::setMatrix2(const string& name, const Matrix2& val)
{
	matrix2s[name] = val;
}

void MappedValues::setString(const string& name, const string& val)
{
	strings[name] = val;
}

Vector2 MappedValues::getVector2(const string& name) const
{
	try
	{
		return vector2s.at(name);
	}
	catch (const std::exception&)
	{
		return Vector2();
	}
}

Vector3 MappedValues::getVector3(const string& name) const
{
	try
	{
		return vector3s.at(name);
	}
	catch (const std::exception&)
	{
		return Vector3();
	}
}

Vector4 MappedValues::getVector4(const string& name) const
{
	try
	{
		return vector4s.at(name);
	}
	catch (const std::exception&)
	{
		return Vector4();
	}
}

F32 MappedValues::getFloat(const string& name) const
{
	try
	{
		return floats.at(name);
	}
	catch (const std::exception&)
	{
		return 0.f;
	}
}

I32 MappedValues::getI32(const string& name) const
{
	try
	{
		return ints.at(name);
	}
	catch (const std::exception&)
	{
		return 0;
	}
}

U32 MappedValues::getU32(const string& name) const
{
	try
	{
		return uints.at(name);
	}
	catch (const std::exception&)
	{
		return 0;
	}
}

Texture* MappedValues::getTexture(const string& name) const
{
	try
	{
		return textures.at(name);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

void* MappedValues::getPointer(const string& name) const
{
	try
	{
		return pointers.at(name);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

UniformStruct* MappedValues::getUniformStruct(const string& name) const
{
	try
	{
		return uniformStructs.at(name);
	}
	catch (const std::exception&)
	{
		return nullptr;
	}
}

Matrix4 MappedValues::getMatrix4(const string& name) const
{
	try
	{
		return matrix4s.at(name);
	}
	catch (const std::exception&)
	{
		return Matrix4();
	}
}

Matrix3 MappedValues::getMatrix3(const string& name) const
{
	try
	{
		return matrix3s.at(name);
	}
	catch (const std::exception&)
	{
		return Matrix3();
	}
}

Matrix2 MappedValues::getMatrix2(const string& name) const
{
	try
	{
		return matrix2s.at(name);
	}
	catch (const std::exception&)
	{
		return Matrix2();
	}
}

string MappedValues::getString(const string& name) const
{
	try
	{
		return strings.at(name);
	}
	catch (const std::exception&)
	{
		return "";
	}
}



void MappedValues::replaceAll(const MappedValues* map)
{
	for (auto& t : textures) {
		resourceManager->freeTexture(t.second);
	}

	for (auto& u : uniformStructs) {
		delete u.second;
	}

	replaceValues(map);

	textures = map->textures;
	uniformStructs = map->uniformStructs;
	pointers = map->pointers;
}

void MappedValues::copyValues(const MappedValues* map)
{
	vector2s.insert(map->vector2s.begin(), map->vector2s.end());
	vector3s.insert(map->vector3s.begin(), map->vector3s.end());
	vector4s.insert(map->vector4s.begin(), map->vector4s.end());
	floats.insert(map->floats.begin(), map->floats.end());
	ints.insert(map->ints.begin(), map->ints.end());
	uints.insert(map->uints.begin(), map->uints.end());
	matrix2s.insert(map->matrix2s.begin(), map->matrix2s.end());
	matrix3s.insert(map->matrix3s.begin(), map->matrix3s.end());
	matrix3s.insert(map->matrix3s.begin(), map->matrix3s.end());
	strings.insert(map->strings.begin(), map->strings.end());
	for (auto a : map->textures) {
		setTexture(a.first, resourceManager->getTexture(a.second->getName()));

	}
}

void MappedValues::replaceValues(const MappedValues* map)
{
	vector2s = map->vector2s;
	vector3s = map->vector3s;
	vector4s = map->vector4s;
	floats = map->floats;
	ints = map->ints;
	uints = map->uints;
	matrix2s = map->matrix2s;
	matrix3s = map->matrix3s;
	matrix4s = map->matrix4s;
	strings = map->strings;
	textures = map->textures;
}

void MappedValues::clear()
{
	vector2s.clear();
	vector3s.clear();
	vector4s.clear();
	floats.clear();
	ints.clear();
	uints.clear();
	matrix2s.clear();
	matrix3s.clear();
	matrix4s.clear();
	pointers.clear();
	uniformStructs.clear();
	strings.clear();

	for (auto& a : textures) {
		resourceManager->freeTexture(a.second);
	}
	textures.clear();

}

void MappedValues::fromJson(const Json::Value& root)
{
	

	Json::Value floats = root["Floats"], ints = root["Ints"], uints = root["Uints"], strings = root["Strings"], vector2s = root["Vector2s"], vector3s = root["Vector3s"], vector4s = root["Vector4s"],
		matrix2s = root["Matrix2s"], matrix3s = root["Matrix3s"], matrix4s = root["Matrix4s"], textures = root["Textures"];

	for (auto i = floats.begin(); i != floats.end(); i++) {
		setFloat(i.name(), (*i).asFloat());
	}

	for (auto i = ints.begin(); i != ints.end(); i++) {
		setI32(i.name(), (*i).asInt());
	}

	for (auto i = uints.begin(); i != uints.end(); i++) {
		setU32(i.name(), (*i).asUInt());
	}

	for (auto i = strings.begin(); i != strings.end(); i++) {
		setString(i.name(), (*i).asString());
	}

	for (auto i = vector2s.begin(); i != vector2s.end(); i++) {
		Vector2 vec((*i)[0].asFloat(), (*i)[1].asFloat());
		setVector2(i.name(), vec);
	}

	for (auto i = vector3s.begin(); i != vector3s.end(); i++) {
		Vector3 vec((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat());
		setVector3(i.name(), vec);
	}

	for (auto i = vector4s.begin(); i != vector4s.end(); i++) {
		Vector4 vec((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat());
		setVector4(i.name(), vec);
	}

	for (auto i = matrix2s.begin(); i != matrix2s.end(); i++) {
		Matrix2 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat());
		setMatrix2(i.name(), mat);
	}

	for (auto i = matrix3s.begin(); i != matrix3s.end(); i++) {
		Matrix3 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat(), (*i)[4].asFloat(), (*i)[5].asFloat(), (*i)[6].asFloat(), (*i)[7].asFloat(), (*i)[8].asFloat());
		setMatrix3(i.name(), mat);
	}

	for (auto i = matrix4s.begin(); i != matrix4s.end(); i++) {
		Matrix4 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat(), (*i)[4].asFloat(), (*i)[5].asFloat(), (*i)[6].asFloat(), (*i)[7].asFloat(), (*i)[8].asFloat(), (*i)[9].asFloat(),
			(*i)[10].asFloat(), (*i)[11].asFloat(), (*i)[12].asFloat(), (*i)[13].asFloat(), (*i)[14].asFloat(), (*i)[15].asFloat());
		setMatrix4(i.name(), mat);
	}

	for (auto i = textures.begin(); i != textures.end(); i++) {
		setTexture(i.name(), resourceManager->fetchTextureLoad((*i).asString()));

	}







}

Json::Value* MappedValues::toJson()
{

	Json::Value* res = new Json::Value;
	Json::Value& root = *res;
	Json::Value floats, ints, uints, strings, vector2s, vector3s, vector4s, matrix2s, matrix3s, matrix4s, textures;

	for (auto& a : getFloats()) {
		floats[a.first] = a.second;
	}

	for (auto& a : getInts()) {
		ints[a.first] = a.second;
	}

	for (auto& a : getUints()) {
		uints[a.first] = a.second;
	}

	for (auto& a : getStrings()) {
		strings[a.first] = a.second.c_str();
	}

	for (auto& a : getVector2s()) {
		vector2s[a.first].append(a.second.x);
		vector2s[a.first].append(a.second.y);
	}

	for (auto& a : getVector3s()) {
		vector3s[a.first].append(a.second.x);
		vector3s[a.first].append(a.second.y);
		vector3s[a.first].append(a.second.z);
	}

	for (auto& a : getVector4s()) {
		vector4s[a.first].append(a.second.x);
		vector4s[a.first].append(a.second.y);
		vector4s[a.first].append(a.second.z);
		vector4s[a.first].append(a.second.w);
	}

	for (auto& a : getMatrix2s()) {
		for (U32 i = 0; i < 4; ++i) matrix2s[a.first].append(a.second.getElement(i));
	}

	for (auto& a : getMatrix3s()) {
		for (U32 i = 0; i < 9; ++i) matrix3s[a.first].append(a.second.getElement(i));
	}

	for (auto& a : getMatrix4s()) {
		for (U32 i = 0; i < 16; ++i) matrix4s[a.first].append(a.second.getElement(i));
	}

	for (auto& a : getTextures()) {

		textures[a.first] = a.second->save();
	}




	root["Floats"] = floats;
	root["Ints"] = ints;
	root["Uints"] = uints;
	root["Strings"] = strings;
	root["Vector2s"] = vector2s;
	root["Vector3s"] = vector3s;
	root["Vector4s"] = vector4s;
	root["Matrix2s"] = matrix2s;
	root["Matrix3s"] = matrix3s;
	root["Matrix4s"] = matrix4s;
	root["Textures"] = textures;

	return res;
}

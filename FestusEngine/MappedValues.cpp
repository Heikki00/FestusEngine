#pragma once
#include "MappedValues.h"
#include "ResourceManager.h"









MappedValues::~MappedValues()
{
	for (auto& t : textures) {
		resourceManager->freeTexture(t.second);
	}

	for (auto& u : uniformStructs) {
		delete u.second;
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
}

#pragma once
#include "json/json.h"

class Texture;
class UniformStruct;

//A class that contains storage for various types. Meant to be inherited from.
class MappedValues {

public:

	virtual ~MappedValues();

	void setVector2(const string& name, const Vector2& val);
	void setVector3(const string& name, const Vector3& val);
	void setVector4(const string& name, const Vector4& val);

	void setFloat(const string& name, F32 val);
	void setI32(const string& name, I32 val);
	void setU32(const string& name, U32 val);

	void setTexture(const string& name, Texture* val);
	void setPointer(const string& name, void* val);

	void setUniformStruct(const string& name, UniformStruct* val);

	void setMatrix4(const string& name, const Matrix4& val);
	void setMatrix3(const string& name, const Matrix3& val);
	void setMatrix2(const string& name, const Matrix2& val);

	void setString(const string& name, const string& val);

	Vector2 getVector2(const string& name) const;
	Vector3 getVector3(const string& name) const;
	Vector4 getVector4(const string& name) const;

	F32 getFloat(const string& name) const;
	I32 getI32(const string& name) const;
	U32 getU32(const string& name) const;

	Texture* getTexture(const string& name) const;
	void* getPointer(const string& name) const;

	UniformStruct* getUniformStruct(const string& name) const;

	Matrix4 getMatrix4(const string& name) const;
	Matrix3 getMatrix3(const string& name) const;
	Matrix2 getMatrix2(const string& name) const;

	string getString(const string& name) const;

	


	void replaceAll(const MappedValues* map);

	void copyValues(const MappedValues* map);
	void replaceValues(const MappedValues* map);

	void clear();

	std::map<string, Vector2> getVector2s() const { return vector2s; }	
	std::map<string, Vector3> getVector3s() const { return vector3s; }	
	std::map<string, Vector4> getVector4s() const { return vector4s; }
	
	std::map<string, Matrix2> getMatrix2s() const { return matrix2s; }	
	std::map<string, Matrix3> getMatrix3s() const { return matrix3s; }
	std::map<string, Matrix4> getMatrix4s() const { return matrix4s; }
	
	std::map<string, float> getFloats() const { return floats; }
	std::map<string, I32> getInts() const { return ints; }
	std::map<string, U32> getUints() const { return uints; }
	
	std::map<string, Texture*> getTextures() const { return textures; }	
	std::map<string, void*> getPointers() const { return pointers; }
	std::map<string, UniformStruct*> getUniformStructs() const { return uniformStructs; }
	
	std::map<string, string> getStrings() const { return strings; }

	void fromJson(const Json::Value& v);

	Json::Value* toJson();

private:
	std::map<string, Vector2> vector2s;
	std::map<string, Vector3> vector3s;
	std::map<string, Vector4> vector4s;

	std::map<string, Matrix2> matrix2s;
	std::map<string, Matrix3> matrix3s;
	std::map<string, Matrix4> matrix4s;

	std::map<string, float> floats;
	std::map<string, I32> ints;
	std::map<string, U32> uints;

	std::map<string, Texture*> textures;
	std::map<string, void*> pointers;

	std::map<string, UniformStruct*> uniformStructs;

	std::map<string, string> strings;
};
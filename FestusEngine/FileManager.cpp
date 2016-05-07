#include "FileManager.h"


std::string FileManager::getContents(const std::string& filename)
{

	std::ifstream is(filename, std::ios::binary);

	if (!is) {
		Debug::log(ErrorType::FILE_ERROR, "Failed to open file: %s\n", filename.c_str());
		return "";
	}

	is.seekg(0, std::ios_base::end);


	std::string result;

	result.reserve((U32)is.tellg());
	is.seekg(0, std::ios_base::beg);

	result.assign((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());


	is.close();

	return result;
}

void FileManager::getContents(const std::string& filename, std::string& res)
{
	std::ifstream is(filename, std::ios::binary);

	if (is.fail()) {
		Debug::log(ErrorType::FILE_ERROR, "Failed to open file: %s\n", filename.c_str());
		return;
	}

	is.seekg(0, std::ios_base::end);



	res.reserve((U32)is.tellg());
	is.seekg(0, std::ios_base::beg);

	res.assign((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());


	is.close();

}

void* FileManager::getContentsPointer(const string& filename, U32* size /*= nullptr*/)
{
	FILE* f = nullptr;
	fopen_s(&f, filename.c_str(), "rb");

	if (!f) {
		Debug::log(ErrorType::FILE_ERROR, "ERROR: Tried to read file that does not exist: %s\n", filename.c_str());
		return nullptr;
	}


	

	fseek(f, 0L, SEEK_END);
	U32 end = ftell(f);
	fseek(f, 0L, SEEK_SET);

	if (size != nullptr) {
		*size = end;
	}


	char* c = new char[end];

	fread_s(c, end, end, 1, f);

	fclose(f);

	return c;




}

U32 FileManager::requestContents(const std::string& filename)
{
	++IDcounter;


	readyStates[IDcounter] = false;
	contents[IDcounter] = "";

	std::thread t(&FileManager::threadReadFile, this, filename, IDcounter);
	t.detach();
	return IDcounter;
}

bool FileManager::isRequestReady(U32 ID)
{
	return readyStates[ID];
}


std::string FileManager::getRequestedContents(U32 request)
{
	while (!isRequestReady(request)) {

		std::unique_lock<std::mutex> ug(mu);
		cv.wait(ug);
	}
	return contents[request];
}


void FileManager::write(const string& filename, const string& contests)
{
	std::ofstream os(filename, std::ios::binary | std::ios::trunc);

	if (os.fail()) {
		Debug::log(ErrorType::FILE_ERROR, "Failed to open file: %s\n", filename.c_str());
		return;
	}

	os << contests;

	os.close();

	
}

void FileManager::append(const string& filename, const string& contents)
{
	std::ofstream os(filename, std::ios::binary |std::ios::app);

	if (os.fail()) {
		Debug::log(ErrorType::FILE_ERROR, "Failed to open file: %s\n", filename.c_str());
		return;
	}

	os << contents;

	os.close();
}

bool FileManager::fileExists(const string& filename)
{

	std::ifstream is(filename);

	return !is.fail();
}

std::string FileManager::toJson(const MappedValues* m)
{
	Json::Value root, floats, ints, uints, strings, vector2s, vector3s, vector4s, matrix2s, matrix3s, matrix4s;
	
	for(auto& a : m->getFloats()){
		floats[a.first] = a.second;
	}

	for (auto& a : m->getInts()) {
		ints[a.first] = a.second;
	}

	for (auto& a : m->getUints()) {
		uints[a.first] = a.second;
	}

	for (auto& a : m->getStrings()) {
		strings[a.first] = a.second;
	}

	for (auto& a : m->getVector2s()) {
		vector2s[a.first].append(a.second.x);
		vector2s[a.first].append(a.second.y);
	}

	for (auto& a : m->getVector3s()) {
		vector3s[a.first].append(a.second.x);
		vector3s[a.first].append(a.second.y);
		vector3s[a.first].append(a.second.z);
	}

	for (auto& a : m->getVector4s()) {
		vector4s[a.first].append(a.second.x);
		vector4s[a.first].append(a.second.y);
		vector4s[a.first].append(a.second.z);
		vector4s[a.first].append(a.second.w);
	}

	for (auto& a : m->getMatrix2s()) {
		for (U32 i = 0; i < 4; ++i) matrix2s[a.first].append(a.second.getElement(i));
	}

	for (auto& a : m->getMatrix3s()) {
		for (U32 i = 0; i < 9; ++i) matrix3s[a.first].append(a.second.getElement(i));
	}

	for (auto& a : m->getMatrix4s()) {
		for (U32 i = 0; i < 16; ++i) matrix4s[a.first].append(a.second.getElement(i));
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


	return Json::StyledWriter().write(root);

}

MappedValues* FileManager::fromJson(const string& src)
{
	MappedValues* m = new MappedValues;


	Json::Reader reader;
	Json::Value root;


	reader.parse(src, root);


	Json::Value floats = root["Floats"], ints = root["Ints"], uints = root["Uints"], strings = root["Strings"], vector2s = root["Vector2s"], vector3s = root["Vector3s"], vector4s = root["Vector4s"], 
		matrix2s = root["Matrix2s"], matrix3s = root["Matrix3s"], matrix4s = root["Matrix4s"];

	for (auto i = floats.begin(); i != floats.end(); i++) {
		m->setFloat(i.name(), (*i).asFloat());
	}

	for (auto i = ints.begin(); i != ints.end(); i++) {
		m->setI32(i.name(), (*i).asInt());
	}

	for (auto i = uints.begin(); i != uints.end(); i++) {
		m->setU32(i.name(), (*i).asUInt());
	}

	for (auto i = strings.begin(); i != strings.end(); i++) {
		m->setString(i.name(), (*i).asString());
	}

	for (auto i = vector2s.begin(); i != vector2s.end(); i++) {
		Vector2 vec((*i)[0].asFloat(), (*i)[1].asFloat());
		m->setVector2(i.name(), vec);
	}

	for (auto i = vector3s.begin(); i != vector3s.end(); i++) {
		Vector3 vec((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat());
		m->setVector3(i.name(), vec);
	}

	for (auto i = vector4s.begin(); i != vector4s.end(); i++) {
		Vector4 vec((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat());
		m->setVector4(i.name(), vec);
	}

	for (auto i = matrix2s.begin(); i != matrix2s.end(); i++) {
		Matrix2 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat());
		m->setMatrix2(i.name(), mat);
	}

	for (auto i = matrix3s.begin(); i != matrix3s.end(); i++) {
		Matrix3 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat(), (*i)[4].asFloat(), (*i)[5].asFloat(), (*i)[6].asFloat(), (*i)[7].asFloat(), (*i)[8].asFloat());
		m->setMatrix3(i.name(), mat);
	}

	for (auto i = matrix4s.begin(); i != matrix4s.end(); i++) {
		Matrix4 mat((*i)[0].asFloat(), (*i)[1].asFloat(), (*i)[2].asFloat(), (*i)[3].asFloat(), (*i)[4].asFloat(), (*i)[5].asFloat(), (*i)[6].asFloat(), (*i)[7].asFloat(), (*i)[8].asFloat(), (*i)[9].asFloat(),
			(*i)[10].asFloat(), (*i)[11].asFloat(), (*i)[12].asFloat(), (*i)[13].asFloat(), (*i)[14].asFloat(), (*i)[15].asFloat());
		m->setMatrix4(i.name(), mat);
	}

	return m;
}

void FileManager::threadReadFile(const std::string& filename, U32 ID)
{
	
	std::ifstream is(filename, std::ios::binary);

	if (!is) {
		Debug::log(ErrorType::FILE_ERROR, "Failed to open file: %s\n", filename.c_str());
		return;
	}

	is.seekg(0, std::ios_base::end);

	

	contents[ID].reserve((U32)is.tellg());
	is.seekg(0, std::ios_base::beg);

	contents[ID].assign((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());


	is.close();

	
	readyStates[ID] = true;
	cv.notify_all();
	
}

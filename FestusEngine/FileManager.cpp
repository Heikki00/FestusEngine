#include "FileManager.h"
#include "Texture.h"

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

Json::Value* FileManager::toJson(const Transform* t)
{
	Json::Value* res = new Json::Value;
	Json::Value& root = *res;
	Json::Value s, r;
	
	
	root["s"] = t->getScale();
	root["rx"] = t->getRotation().x;
	root["ry"] = t->getRotation().y;
	root["rz"] = t->getRotation().z;
	root["rw"] = t->getRotation().w;

	root["px"] = t->getPosition().x;
	root["py"] = t->getPosition().y;
	root["pz"] = t->getPosition().z;


	return res;
}


void FileManager::fromJson(Json::Value& root, Transform* t)
{
	if (!t) t = new Transform;





	t->setScale(root["s"].asFloat());


	t->setPosition(Vector3(root["px"].asFloat(), root["py"].asFloat(), root["pz"].asFloat()));

	t->setRotation(Quaternion(root["rx"].asFloat(), root["ry"].asFloat(), root["rz"].asFloat(), root["rw"].asFloat()));

}




Json::Value* FileManager::parseJson(const string& src)
{
	Json::Value* val = new Json::Value;
	Json::Reader().parse(src, *val);
	
	return val;
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

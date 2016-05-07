#pragma once
#include "Debug.h"


#define MASTER_FILE "MasterLog.log"

std::mutex Debug::internals::mutex;
U32 Debug::internals::whatToPrint = 0xFFFFFFFFFFFFFFFF;

void Debug::log(U32 e, const char* message, ...)
{
	Debug::internals::mutex.lock();

	va_list argptr;
	FILE* file = fopen(MASTER_FILE, "a");

	if (!file) {
		fprintf(
			stderr,
			"ERROR: could not open Master log file %s file for appending\n",
			MASTER_FILE
			);
	
	}
	else {
		va_start(argptr, message);
		vfprintf(file, message, argptr);
		va_end(argptr);
		fclose(file);
	
	}

	auto v = Debug::internals::getFilenames(e);
	for (auto s : v) {
		file = fopen(s.c_str(), "a");
		va_start(argptr, message);
		vfprintf(file, message, argptr);
		va_end(argptr);

		fclose(file);
	
	}
	
	if (e & Debug::internals::whatToPrint) {
		//Print
		va_start(argptr, message);
		vfprintf(stderr, message, argptr);
		va_end(argptr);
	}




	Debug::internals::mutex.unlock();



}

void Debug::init()
{
	auto v = internals::getFilenames(0xFFFFFF);

	FILE* file = nullptr;
	fopen_s(&file, MASTER_FILE, "w");
	if (!file) fprintf(stderr, "Debug failed to empty file %s\n", MASTER_FILE);
	if (file) fclose(file);

	for (string s : v) {
		
		fopen_s(&file, s.c_str(), "w");
		if (!file) fprintf(stderr, "Debug failed to empty file %s\n", s.c_str());
		if (file) fclose(file);
	}

	



}

void Debug::setWhatToPrint(U32 mask)
{
	
	Debug::internals::whatToPrint = mask;
}

U32 Debug::getWhatToPrint()
{
	return Debug::internals::whatToPrint;
}



#define XORERROR(var, type) var = var ^ type;

std::vector<std::string> Debug::internals::getFilenames(U32 errortype)
{
	std::vector<std::string> v;
	
	
	while (errortype != 0) {
		switch (errortype)
		{
		case ErrorType::CRITICAL_ERROR: { v.push_back("Critical.log"); XORERROR(errortype, ErrorType::CRITICAL_ERROR)}
		case ErrorType::LOG: { v.push_back("Log.log"); XORERROR(errortype, ErrorType::LOG)}
		case ErrorType::FILE_ERROR: { v.push_back("FileError.log"); XORERROR(errortype, ErrorType::FILE_ERROR)}
		case ErrorType::SHADER_ERROR: { v.push_back("ShaderError.log"); XORERROR(errortype, ErrorType::SHADER_ERROR)}
		case ErrorType::RESOURCE_ERROR: { v.push_back("ResourceError.log"); XORERROR(errortype, ErrorType::RESOURCE_ERROR)}
		case ErrorType::TEXTURE_ERROR: { v.push_back("TextureError.log"); XORERROR(errortype, ErrorType::TEXTURE_ERROR)}
		case ErrorType::OPENGL_ERROR: { v.push_back("OpenGLError.log"); XORERROR(errortype, ErrorType::OPENGL_ERROR)}
		default: errortype = 0;
		}
	}
	return v;
}

#undef XORERROR
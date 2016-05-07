#pragma once
#include <mutex>
#include <atomic>

//A class that contains various functions for file IO
class FileManager {
public:

	//Returns the contents of a file. Blocking function. If filename is not valid, logs an error and returns an empty string
	std::string getContents(const std::string& filename);

	//writes the contents of a file to res. Blocking function. If filename is not valid, logs an error and returns an empty string
	void getContents(const std::string& filename, std::string& res);

	//Reads the file and returns a pointer to the start of it
	void* getContentsPointer(const string& filename, U32* size = nullptr);

	//Starts a new thread that reads file. Returns ID that is used to retrieve data.
	U32 requestContents(const std::string& filename);

	//Returns true if request is ready, false otherwise
	bool isRequestReady(U32 requestID);

	//Returns the contents requested by ID. If not ready yet, waits for read to be ready.
	std::string getRequestedContents(U32 requestID);

	//Writes a string to a file.
	void write(const string& filename, const string& contests);

	//Appends a string to a file
	void append(const string& filenam, const string& contents);

	//Does the file exist?
	bool fileExists(const string& filename);

	//Translates MappedValues to json
	std::string toJson(const MappedValues* m);

	//Constructs MappedValues from json
	MappedValues* fromJson(const string& src);

private:

	std::condition_variable cv;
	std::mutex mu;

	U32 IDcounter = 0;

	std::map<U32, std::atomic<bool>> readyStates;
	std::map<U32, std::string> contents;

	//Function used with threads
	void threadReadFile(const std::string& filename, U32 ID);

};
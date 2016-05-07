#pragma once


namespace ErrorType {
	enum : U32 {
		CRITICAL_ERROR = 1 << 0,
		LOG = 1 << 1,
		FILE_ERROR = 1 << 2,
		SHADER_ERROR = 1 << 3,
		RESOURCE_ERROR = 1 << 4,
		TEXTURE_ERROR = 1 << 5,
		OPENGL_ERROR = 1 << 6
	};

};



namespace Debug {

	//Writes to the log file of errortype, and to the master file. Might print the error. Thread-safe
	void log(U32 errortype, const char* message, ...);
 

	//Clears all old logs.
	void init();
	
	
	//Sets mask for what to print. Use like this: setWhatToPrint(CRITICAL | FILE | LOG). If error's bit is 0, it will not be printed, and if it is 1, it will be printed. Only main thread should call this or getWhatToPrint()
	void setWhatToPrint(U32 mask);

	//Returns printing mask. Look to setWhatToPrint for more info.
	U32 getWhatToPrint();

	
	//TODO: debug drawing, user can set if messages are printed for particular error type




	

	namespace internals {
		extern U32 whatToPrint;
		extern std::mutex mutex;
		

		std::vector<std::string> getFilenames(U32 errortype);
	};






};











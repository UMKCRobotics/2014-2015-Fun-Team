#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

/**
 * Singleton logger class
 *
 * Defaults to cout and prepending "Message: " to messages and 
 * "Error: " to errors
 *
 * Usage:
 *
 * //Initialies the stream to cout, the message prefix to "Message: "
 * //and the error prefix to "Error: "
 * Logger::standardInit(); 
 *
 * //Logs "Message: This is a message" to standard output
 * Logger::logMessage("This is a message");
 * 
 * //Logs "Error: This is an error" to standard output
 * Logger::logError("This is an error");
 *
 * //Set the logger to a file stream
 * fstream fout("/tmp/log.txt");
 * Logger::setStream(&fout);
 *
 * //Set the Message Prefixes
 * Logger::setMessagePrefix("M: ");
 * Logger::setErrorPrefix("E: ");
 */
class Logger{
private:
	ostream* os;
	string errorPrefix;
	string messagePrefix;
	stringstream ss;
	void init();
	/*
	 * Logs and clears what's current in the stringstream
	 */
	void log();
	void p_setStream(ostream* out);
	bool checkStream(bool setToCout=true);

	template<typename Func>
	static void applyToLoggerInstance(Func f);
public:
	static Logger& getInstance(){
		static Logger instance;
		return instance;
	}

	/*
	 * Sets the stream object to stream to, must be passed as a pointer
	 */
	static void setStream(ostream* out);
	/*
	 * Logs a message to the set stream with the standard message prefix
	 */
	static void logMessage(string message);
	/*
	 * Logs an error to the set stream with the standard message prefix
	 */
	static void logError(string error);
	/*
	 * Logs a message to the set stream with the standard error prefix
	 */
	static void setMessagePrefix(string s);
	/*
	 * Sets the prefix for all error messages
	 */
	static void setErrorPrefix(string s);
	/*
	 * Sets teh prefix for all messages
	 */
	static void standardInit();
};
	
#endif

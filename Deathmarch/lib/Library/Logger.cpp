#include "Logger.h"
#include <iostream>
#include <stdexcept>

using std::endl;

void Logger::log(){
	(*os) << ss.str();
	ss.str(std::string());
}

void Logger::logMessage(string message)
{
	Logger::applyToLoggerInstance([&message](Logger* instance){
		instance->checkStream();
		instance->ss << instance->messagePrefix << message << endl;
		instance->log();
		});
}

void Logger::logError(string error)
{
	Logger::applyToLoggerInstance([&error](Logger* instance){
		instance->checkStream();
		instance->ss << instance->errorPrefix << error << endl;
		instance->log();
		});

}
void Logger::p_setStream(ostream* out){
	os = out;
}
void Logger::setStream(ostream* out){
	Logger::getInstance().p_setStream(out);	
}

bool Logger::checkStream(bool setToCout){
	
	if(Logger::getInstance().os == NULL){
		if(setToCout){
			Logger::getInstance().setStream(&cout);
		}
		return false;
	}
	return true;
}
void Logger::init()
{
}

void Logger::setErrorPrefix(string s)
{
	Logger::getInstance().errorPrefix = s;
}

void Logger::setMessagePrefix(string s)
{
	Logger::getInstance().messagePrefix = s;
}

void Logger::standardInit()
{
	Logger::setStream(&std::cout);
	Logger::setErrorPrefix("Error : ");
	Logger::setMessagePrefix("Message : ");
}
template<typename Func>
void Logger::applyToLoggerInstance(Func f)
{
	Logger* instance = &Logger::getInstance();
	f(instance);
}


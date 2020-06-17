#include "Logger.h"

namespace OSE {

	Logger* Logger::instance;

	Logger::Logger() {
	}

	Logger::~Logger() {
	}

	void Logger::Log(int LogLevel, string message) {
		if (LogLevel > 0) {
			std::cout << "OSE:";
		}
		else {
			std::cout << S_APP_NAME << ":";
		}
		switch (LogLevel & -LogLevel) {
		case LOG_OSE_TRACE:
			std::cout << "TRACE     <";
			break;
		case LOG_OSE_INFO:
			std::cout << "INFO      <";
			break;
		case LOG_OSE_WARNING:
			std::cout << "WARNING   <";
			break;
		case LOG_OSE_ERROR:
			std::cout << "ERROR     <";
		}
		std::cout << message << std::endl;
	}

	void Logger::Start() {
		#ifndef OSE_DISABLE_LOGGER
		Logger::instance = this;
		OSE_LOG(LOG_OSE_INFO, "Logger started!");
		#endif
	}

	void Logger::Stop() {
		#ifndef OSE_DISABLE_LOGGER
		OSE_LOG(LOG_OSE_INFO, "Logger stopped!");
		Logger::instance = nullptr;
		#endif
	}
}
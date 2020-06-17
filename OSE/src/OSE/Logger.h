#ifndef OSE_LOGGER_H
#define OSE_LOGGER_H

#include "Core.h"

#include <iostream>
#include <string>

namespace OSE {

	using std::string;

	#define LOG_OSE_TRACE   1
	#define LOG_OSE_INFO    2
	#define LOG_OSE_WARNING 3
	#define LOG_OSE_ERROR   4

	#define LOG_APP_TRACE   -1
	#define LOG_APP_INFO    -2
	#define LOG_APP_WARNING -3
	#define LOG_APP_ERROR   -4

	class OSE_API Logger
	{
	public:
		static Logger* instance;

		Logger();
		~Logger();

		void Log(int LogLevel, string message);

		void Start();

		void Stop();
	};
}

#ifdef OSE_DISABLE_LOGGER
#define OSE_LOG(...)
#else
#define OSE_LOG(...)	::OSE::Logger::instance->Log(__VA_ARGS__);
#endif // !OSE_DISABLE_LOGGER


#endif
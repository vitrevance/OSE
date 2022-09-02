#ifndef OSE_LOGGER_H
#define OSE_LOGGER_H

#include <OSE/Core.h>
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

	class OSE_API Logger {
	public:
		static Logger* instance;

		Logger();
		~Logger();

		template<class T>
		void Log(int LogLevel, const T& message) {
#ifndef OSE_DISABLE_LOGGER
			if (std::abs(LogLevel) < this->m_logLevel) {
				return;
			}
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
#endif
		}

		void Start();

		void Stop();

		void setLogLevel(int level);
	private:
		int m_logLevel;
	};

	template<typename T>
	string to_str(const T& x) {
		string res = "";
		t_float* ptr = (t_float*)(&x);
		int size = sizeof(x) / sizeof(t_float);
		for (int i = 0; i < size; i++) {
			res += std::to_string(ptr[i]);
			if (i + 1 < size) {
				res += " ";
			}
		}
		return res;
	}
}
#ifndef OSE_DISABLE_LOGGER
#define OSE_LOG(...);	::OSE::Logger::instance->Log(__VA_ARGS__)
#else
#define OSE_LOG(...)
#endif

#endif
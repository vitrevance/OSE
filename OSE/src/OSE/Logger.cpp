#include <OSE/Logger.hpp>

namespace OSE {

Logger* Logger::instance;

Logger::Logger()
    : m_logLevel(0) {
}

Logger::~Logger() {
}

void Logger::start() {
#ifndef OSE_DISABLE_LOGGER
  Logger::instance = this;
  OSE_LOG(LOG_OSE_INFO, "Logger started!");
#endif
}

void Logger::stop() {
#ifndef OSE_DISABLE_LOGGER
  OSE_LOG(LOG_OSE_INFO, "Logger stopped!");
  Logger::instance = nullptr;
#endif
}

void Logger::setLogLevel(int level) {
  this->m_logLevel = level;
}
}  // namespace OSE

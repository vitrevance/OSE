#include <OSE/DebugData.hpp>

#include <OSE/Logger.hpp>

namespace DebugData {

std::unique_ptr<Manager> Manager::instance = std::make_unique<Manager>();

void Manager::printError(const std::string& message) {
  OSE_LOG(LOG_OSE_ERROR, message);
}

}  // namespace DebugData
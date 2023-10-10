#include <OSE/DebugData.hpp>

namespace DebugData {
std::unique_ptr<Manager> Manager::instance = std::make_unique<Manager>();
}
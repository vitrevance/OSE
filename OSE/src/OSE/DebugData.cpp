#include "DebugData.h"

namespace DebugData {
	std::unique_ptr<Manager> Manager::instance = std::make_unique<Manager>();
}
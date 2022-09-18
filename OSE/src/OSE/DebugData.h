#ifndef OSE_DEBUGDATA_H
#define OSE_DEBUGDATA_H

#include <OSE/Core.h>
#include <iostream>
#include <any>
#include <memory>

namespace DebugData {
	// OSE_API extern float hit_pos[4];
	class OSE_API Manager {
	public:
		static std::unique_ptr<Manager> instance;
		
		template<typename T>
		inline void put(std::string id, const T& value) {
			m_data[id] = value;
		}

		template<typename T>
		inline T& get(const std::string& id) {
			if (!m_data.count(id)) {
				// ::OSE::Logger::instance->Log(3, "Accessing unset debug variable: " + id);
				std::cout << "Accessing unset debug variable: " << id << std::endl;
				m_data[id] = T();
			}
			return std::any_cast<std::remove_reference_t<T>&>(m_data[id]);
		}
	private:
		std::map<std::string, std::any> m_data;
	};
}

#endif
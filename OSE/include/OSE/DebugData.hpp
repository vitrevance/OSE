#ifndef OSE_DEBUGDATA_H
#define OSE_DEBUGDATA_H

#ifndef OSE_BUILD
#error Do not use in application!
#endif

#include <any>
#include <memory>
#include <string>
#include <map>

namespace DebugData {
class Manager {
 public:
  static std::unique_ptr<Manager> instance;

  template <typename T>
  inline void put(std::string id, const T& value) {
    m_data[id] = value;
  }

  template <typename T>
  inline T& get(const std::string& id) {
    if (!m_data.count(id)) {
      printError("Accessing unset debug variable: " + id);
      m_data[id] = T();
    }
    return std::any_cast<std::remove_reference_t<T>&>(m_data[id]);
  }

 private:
  void printError(const std::string& message);
  std::map<std::string, std::any> m_data;
};
}  // namespace DebugData

#endif
#ifndef OSE_CONVEX_H
#define OSE_CONVEX_H

#include <OSE/Math/Vecmath.hpp>

namespace OSE {
class OSE_API Convex {
 public:
  std::set<vec4> vertices;
  void* parent;

  Convex();
  ~Convex() = default;
};
}  // namespace OSE

#endif

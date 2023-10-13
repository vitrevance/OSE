#ifndef OSE_ROTOR_H
#define OSE_ROTOR_H

#include <OSE/Math/Vecmath.hpp>

namespace OSE {
class OSE_API Rotor4 {
 public:
  float v0;
  Bivector4 v2;
  float v4;

  Rotor4();

  Rotor4(const vec4& a, const vec4& b);

  Rotor4 reverse() const;
  void rotate(const Rotor4& r);
  Multivector4 asMultivector() const;

  static Rotor4 fromMultivector(const Multivector4& value);
  static Rotor4 xy(float angle);
  static Rotor4 yz(float angle);
  static Rotor4 xz(float angle);
  static Rotor4 xw(float angle);
  static Rotor4 yw(float angle);
  static Rotor4 zw(float angle);
};

Rotor4 OSE_API operator*(const Rotor4& a, const Rotor4& b);
vec4 OSE_API operator*(const Rotor4& r, const vec4& a);
}  // namespace OSE

#endif
#ifndef OSE_BIVECTOR_H
#define OSE_BIVECTOR_H

#include <OSE/Math/Vector.hpp>

namespace OSE {
class OSE_API Bivector4 {
 public:
  float xy, yz, xz, xw, yw, zw;

  Bivector4();
  Bivector4(float xy, float yz, float xz, float xw, float yw,
            float zw);

  float value() const;

  Bivector4 operator+(const Bivector4& a) const;
  Bivector4 operator-(const Bivector4& a) const;
  Bivector4 operator-() const;
  Bivector4 operator*(float a) const;
  void operator+=(const Bivector4& a);
};

class OSE_API Trivector4 {
 public:
  float xyz, yzw, xyw, xzw;

  Trivector4();
  Trivector4(float xyz, float yzw, float xyw, float xzw);

  Trivector4 abs() const;
  float value() const;

  Trivector4 operator+(const Trivector4& a) const;
  Trivector4 operator-(const Trivector4& a) const;
  Trivector4 operator-() const;
  Trivector4 operator*(float a) const;
  bool operator==(const Trivector4& a) const;
};

class OSE_API Tetravector4 {
 public:
  float xyzw;

  Tetravector4();
  Tetravector4(float xyzw);

  Tetravector4 operator+(const Tetravector4& a) const;
  Tetravector4 operator-(const Tetravector4& a) const;
  Tetravector4 operator-() const;
  Tetravector4 operator*(float a) const;
};

class OSE_API Multivector4 {
 public:
  float v0;
  vec4 v1;
  Bivector4 v2;
  Trivector4 v3;
  Tetravector4 v4;

  Multivector4();
  Multivector4(float scalar, const vec4& x, const Bivector4& xy,
               const Trivector4& xyz, const Tetravector4& xyzw);
  explicit Multivector4(float scalar);
  explicit Multivector4(const vec4& x);
  explicit Multivector4(const Bivector4& xy);
  explicit Multivector4(const Trivector4& xyz);
  explicit Multivector4(const Tetravector4& xyzw);

  Multivector4 operator+(const Multivector4& a) const;
  Multivector4 operator-(const Multivector4& a) const;
};
}  // namespace OSE

#endif
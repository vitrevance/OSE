#ifndef OSE_RANDOM_H
#define OSE_RANDOM_H

#include <OSE/Core.hpp>
#include <OSE/Math/Vecmath.hpp>

namespace OSE {
namespace Random {

int Integer() {
  return rand();
}

int Integer(int low, int high) {
  return rand() % high + low;
}

float Decimal() {
  return (float)rand() / RAND_MAX;
}

float Decimal(int decimalPoints) {
  float div = pow(10, decimalPoints);
  return (float)Integer(0, div + 1) / div;
}

float SignedDecimal() {
  return Decimal() * 2 - 1;
}

vec2 Vector2() {
  vec2 result;
  for (unsigned int i = 0; i < 2; i++) {
    result[i] = SignedDecimal() * Integer();
  }
  return result;
}

vec3 Vector3() {
  vec3 result;
  for (unsigned int i = 0; i < 3; i++) {
    result[i] = SignedDecimal() * Integer();
  }
  return result;
}

vec4 Vector4() {
  vec4 result;
  for (unsigned int i = 0; i < 4; i++) {
    result[i] = SignedDecimal() * Integer();
  }
  return result;
}

vec2 Normal2() {
  return (Vector2()).normalized();
}

vec3 Normal3() {
  return (Vector3()).normalized();
}

vec4 Normal4() {
  return (Vector4()).normalized();
}

vec2 Vector2(float maxLength) {
  return Normal2() * Decimal() * maxLength;
}

vec3 Vector3(float maxLength) {
  return Normal3() * Decimal() * maxLength;
}

vec4 Vector4(float maxLength) {
  return Normal4() * Decimal() * maxLength;
}
}  // namespace Random
}  // namespace OSE

#endif
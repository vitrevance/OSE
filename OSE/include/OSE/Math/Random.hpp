#ifndef OSE_RANDOM_H
#define OSE_RANDOM_H

#include <OSE/Core.hpp>
#include <OSE/Math/Vecmath.hpp>

namespace OSE {
namespace Random {

int integer() {
  return rand();
}

int integer(int low, int high) {
  return rand() % high + low;
}

float decimal() {
  return (float)rand() / RAND_MAX;
}

float decimal(int decimalPoints) {
  float div = pow(10, decimalPoints);
  return (float)integer(0, div + 1) / div;
}

float signedDecimal() {
  return decimal() * 2 - 1;
}

vec2 vector2() {
  vec2 result;
  for (unsigned int i = 0; i < 2; i++) {
    result[i] = signedDecimal() * integer();
  }
  return result;
}

vec3 vector3() {
  vec3 result;
  for (unsigned int i = 0; i < 3; i++) {
    result[i] = signedDecimal() * integer();
  }
  return result;
}

vec4 vector4() {
  vec4 result;
  for (unsigned int i = 0; i < 4; i++) {
    result[i] = signedDecimal() * integer();
  }
  return result;
}

vec2 normal2() {
  return (vector2()).normalized();
}

vec3 normal3() {
  return (vector3()).normalized();
}

vec4 normal4() {
  return (vector4()).normalized();
}

vec2 vector2(float maxLength) {
  return normal2() * decimal() * maxLength;
}

vec3 vector3(float maxLength) {
  return normal3() * decimal() * maxLength;
}

vec4 vector4(float maxLength) {
  return normal4() * decimal() * maxLength;
}
}  // namespace Random
}  // namespace OSE

#endif
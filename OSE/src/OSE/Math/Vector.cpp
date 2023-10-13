#include <OSE/Math/Vector.hpp>

namespace OSE {
// vec2
vec2::vec()
    : x(0),
      y(0) {
}
vec2::vec(float x, float y)
    : x(x),
      y(y) {
}
vec2::vec(float v)
    : x(v),
      y(v) {
}

float vec2::length() const {
  return sqrt(this->x * this->x + this->y * this->y);
}

void vec2::normalize() {
  *this /= this->length();
}

vec2 vec2::normalized() const {
  return *this / this->length();
}

float& vec2::operator[](unsigned int i) {
  return ((float*)this)[i];
}

vec2 vec2::operator+(const vec2& a) const {
  return vec2(this->x + a.x, this->y + a.y);
}

vec2 vec2::operator-(const vec2& a) const {
  return vec2(this->x + a.x, this->y + a.y);
}

vec2 vec2::operator*(float a) const {
  return vec2(this->x * a, this->y * a);
}

vec2 vec2::operator/(float a) const {
  return vec2(this->x / a, this->y / a);
}

void vec2::operator+=(const vec2& a) {
  this->x += a.x;
  this->y += a.y;
}

void vec2::operator-=(const vec2& a) {
  this->x -= a.x;
  this->y -= a.y;
}

void vec2::operator*=(float a) {
  this->x *= a;
  this->y *= a;
}

void vec2::operator/=(float a) {
  this->x /= a;
  this->y /= a;
}
// vec3
vec3::vec()
    : x(0),
      y(0),
      z(0) {
}
vec3::vec(float x, float y, float z)
    : x(x),
      y(y),
      z(z) {
}
vec3::vec(float v)
    : x(v),
      y(v),
      z(v) {
}
vec3::vec(vec2 xy, float z)
    : x(xy.x),
      y(xy.y),
      z(z) {
}
vec3::vec(float x, vec2 yz)
    : x(x),
      y(yz.x),
      z(yz.y) {
}

float vec3::length() const {
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void vec3::normalize() {
  *this /= this->length();
}

vec3 vec3::normalized() const {
  return *this / this->length();
}

float& vec3::operator[](unsigned int i) {
  return ((float*)this)[i];
}

vec3 vec3::operator+(const vec3& a) const {
  return vec3(this->x + a.x, this->y + a.y, this->z + a.z);
}

vec3 vec3::operator-(const vec3& a) const {
  return vec3(this->x - a.x, this->y - a.y, this->z - a.z);
}

vec3 vec3::operator*(float a) const {
  return vec3(this->x * a, this->y * a, this->z * a);
}

vec3 vec3::operator/(float a) const {
  return vec3(this->x / a, this->y / a, this->z / a);
}

void vec3::operator+=(const vec3& a) {
  this->x += a.x;
  this->y += a.y;
  this->z += a.z;
}

void vec3::operator-=(const vec3& a) {
  this->x -= a.x;
  this->y -= a.y;
  this->z -= a.z;
}

void vec3::operator*=(float a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
}

void vec3::operator/=(float a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
}
// vec4
vec4::vec()
    : x(0),
      y(0),
      z(0),
      w(0) {
}
vec4::vec(float x, float y, float z, float w)
    : x(x),
      y(y),
      z(z),
      w(w) {
}
vec4::vec(float v)
    : x(v),
      y(v),
      z(v),
      w(v) {
}
vec4::vec(vec2 xy, float z, float w)
    : x(xy.x),
      y(xy.y),
      z(z),
      w(w) {
}
vec4::vec(float x, vec2 yz, float w)
    : x(x),
      y(yz.x),
      z(yz.y),
      w(w) {
}
vec4::vec(float x, float y, vec2 zw)
    : x(x),
      y(y),
      z(zw.x),
      w(zw.y) {
}
vec4::vec(vec3 xyz, float w)
    : x(xyz.x),
      y(xyz.y),
      z(xyz.z),
      w(w) {
}
vec4::vec(float x, vec3 yzw)
    : x(x),
      y(yzw.x),
      z(yzw.y),
      w(yzw.z) {
}

float vec4::length() const {
  return sqrt(this->x * this->x + this->y * this->y + this->z * this->z +
              this->w * this->w);
}

void vec4::normalize() {
  *this /= this->length();
}

vec4 vec4::normalized() const {
  return *this / this->length();
}

float& vec4::operator[](unsigned int i) {
  return ((float*)this)[i];
}

vec4 vec4::operator+(const vec4& a) const {
  return vec4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
}

vec4 vec4::operator-(const vec4& a) const {
  return vec4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
}

vec4 vec4::operator*(float a) const {
  return vec4(this->x * a, this->y * a, this->z * a, this->w * a);
}

vec4 vec4::operator/(float a) const {
  return vec4(this->x / a, this->y / a, this->z / a, this->w / a);
}

vec4 vec4::operator-() const {
  return vec4(-this->x, -this->y, -this->z, -this->w);
}

void vec4::operator+=(const vec4& a) {
  this->x += a.x;
  this->y += a.y;
  this->z += a.z;
  this->w += a.w;
}

void vec4::operator-=(const vec4& a) {
  this->x -= a.x;
  this->y -= a.y;
  this->z -= a.z;
  this->w -= a.w;
}

void vec4::operator*=(float a) {
  this->x *= a;
  this->y *= a;
  this->z *= a;
  this->w *= a;
}

void vec4::operator/=(float a) {
  this->x /= a;
  this->y /= a;
  this->z /= a;
  this->w /= a;
}
}  // namespace OSE
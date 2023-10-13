#include <OSE/Math/Multivector.hpp>

namespace OSE {

Bivector4::Bivector4()
    : xy(0),
      yz(0),
      xz(0),
      xw(0),
      yw(0),
      zw(0) {
}
Bivector4::Bivector4(float xy, float yz, float xz, float xw, float yw,
                     float zw)
    : xy(xy),
      yz(yz),
      xz(xz),
      xw(xw),
      yw(yw),
      zw(zw) {
}

float Bivector4::value() const {
  return this->xy * this->xy + this->yz * this->yz + this->xz * this->xz +
         this->xw * this->xw + this->yw * this->yw + this->zw * this->zw;
}

Bivector4 Bivector4::operator+(const Bivector4& a) const {
  return Bivector4(this->xy + a.xy, this->yz + a.yz, this->xz + a.xz,
                   this->xw + a.xw, this->yw + a.yw, this->zw + a.zw);
}

Bivector4 Bivector4::operator-(const Bivector4& a) const {
  return Bivector4(this->xy - a.xy, this->yz - a.yz, this->xz - a.xz,
                   this->xw - a.xw, this->yw - a.yw, this->zw - a.zw);
}

Bivector4 Bivector4::operator-() const {
  return Bivector4(-this->xy, -this->yz, -this->xz, -this->xw, -this->yw,
                   -this->zw);
}

Bivector4 Bivector4::operator*(float a) const {
  return Bivector4(this->xy * a, this->yz * a, this->xz * a, this->xw * a,
                   this->yw * a, this->zw * a);
}

void Bivector4::operator+=(const Bivector4& a) {
  *this = *this + a;
}

Trivector4::Trivector4()
    : xyz(0),
      yzw(0),
      xyw(0),
      xzw(0) {
}
Trivector4::Trivector4(float xyz, float yzw, float xyw, float xzw)
    : xyz(xyz),
      yzw(yzw),
      xyw(xyw),
      xzw(xzw) {
}

Trivector4 Trivector4::abs() const {
  return Trivector4(std::abs(this->xyz), std::abs(this->yzw),
                    std::abs(this->xyw), std::abs(this->xzw));
}

float Trivector4::value() const {
  return this->xyw * this->xyw + this->xyz * this->xyz + this->xzw * this->xzw +
         this->yzw * this->yzw;
}

Trivector4 Trivector4::operator+(const Trivector4& a) const {
  return Trivector4(this->xyz + a.xyz, this->yzw + a.yzw, this->xyw + a.xyw,
                    this->xzw + a.xzw);
}

Trivector4 Trivector4::operator-(const Trivector4& a) const {
  return Trivector4(this->xyz - a.xyz, this->yzw - a.yzw, this->xyw - a.xyw,
                    this->xzw - a.xzw);
}

Trivector4 Trivector4::operator-() const {
  return Trivector4(-this->xyz, -this->yzw, -this->xyw, -this->xzw);
}

Trivector4 Trivector4::operator*(float a) const {
  return Trivector4(this->xyz * a, this->yzw * a, this->xyw * a, this->xzw * a);
}

bool Trivector4::operator==(const Trivector4& a) const {
  return this->xyz == a.xyz && this->yzw == a.yzw && this->xyw == a.xyw &&
         this->xzw == a.xzw;
}

Tetravector4::Tetravector4()
    : xyzw(0) {
}
Tetravector4::Tetravector4(float xyzw)
    : xyzw(xyzw) {
}

Tetravector4 Tetravector4::operator+(const Tetravector4& a) const {
  return Tetravector4(this->xyzw + a.xyzw);
}

Tetravector4 Tetravector4::operator-(const Tetravector4& a) const {
  return Tetravector4(this->xyzw - a.xyzw);
}

Tetravector4 Tetravector4::operator-() const {
  return Tetravector4(-this->xyzw);
}

Tetravector4 Tetravector4::operator*(float a) const {
  return Tetravector4(this->xyzw * a);
}

Multivector4::Multivector4()
    : v0(0) {
}

Multivector4::Multivector4(float scalar, const vec4& x, const Bivector4& xy,
                           const Trivector4& xyz, const Tetravector4& xyzw)
    : v0(scalar),
      v1(x),
      v2(xy),
      v3(xyz),
      v4(xyzw) {
}

Multivector4::Multivector4(float scalar)
    : v0(scalar) {
}

Multivector4::Multivector4(const Bivector4& xy)
    : v0(0),
      v2(xy) {
}

Multivector4::Multivector4(const Trivector4& xyz)
    : v0(0),
      v3(xyz) {
}

Multivector4::Multivector4(const Tetravector4& xyzw)
    : v0(0),
      v4(xyzw) {
}

Multivector4 Multivector4::operator+(const Multivector4& a) const {
  Multivector4 result;
  result.v0 = this->v0 + a.v0;
  result.v1 = this->v1 + a.v1;
  result.v2 = this->v2 + a.v2;
  result.v3 = this->v3 + a.v3;
  result.v4 = this->v4 + a.v4;
  return result;
}

Multivector4 Multivector4::operator-(const Multivector4& a) const {
  Multivector4 result;
  result.v0 = this->v0 - a.v0;
  result.v1 = this->v1 - a.v1;
  result.v2 = this->v2 - a.v2;
  result.v3 = this->v3 - a.v3;
  result.v4 = this->v4 - a.v4;
  return result;
}
}  // namespace OSE
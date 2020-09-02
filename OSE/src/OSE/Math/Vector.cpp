#include <OSE/Math/Vector.h>

namespace OSE {
	//vec2
	vec2::vec2() : x(0), y(0) {}
	vec2::vec2(t_float x, t_float y) : x(x), y(y) {}
	vec2::vec2(t_float v) : x(v), y(v) {}

	t_float vec2::length() {
		return sqrt(this->x*this->x + this->y*this->y);
	}

	void vec2::normalize() {
		*this /= this->length();
	}

	vec2 vec2::normalized() {
		return *this / this->length();
	}

	t_float& vec2::operator[] (unsigned int i) {
		return ((t_float*)this)[i];
	}

	vec2 vec2::operator+ (const vec2& a) const {
		return vec2(this->x + a.x, this->y + a.y);
	}

	vec2 vec2::operator- (const vec2& a) const {
		return vec2(this->x + a.x, this->y + a.y);
	}

	vec2 vec2::operator* (t_float a) const {
		return vec2(this->x * a, this->y * a);
	}

	vec2 vec2::operator/ (t_float a) const {
		return vec2(this->x / a, this->y / a);
	}

	void vec2::operator+= (const vec2& a) {
		this->x += a.x;
		this->y += a.y;
	}

	void vec2::operator-= (const vec2& a) {
		this->x -= a.x;
		this->y -= a.y;
	}

	void vec2::operator*= (t_float a) {
		this->x *= a;
		this->y *= a;
	}

	void vec2::operator/= (t_float a) {
		this->x /= a;
		this->y /= a;
	}
	//vec3
	vec3::vec3() : x(0), y(0), z(0) {}
	vec3::vec3(t_float x, t_float y, t_float z) : x(x), y(y), z(z) {}
	vec3::vec3(t_float v) : x(v), y(v), z(v) {}
	vec3::vec3(vec2 xy, t_float z) : xy(xy), _z(z) {}
	vec3::vec3(t_float x, vec2 yz) : _x(x), yz(yz) {}

	t_float vec3::length() {
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	void vec3::normalize() {
		*this /= this->length();
	}

	vec3 vec3::normalized() {
		return *this / this->length();
	}

	t_float& vec3::operator[] (unsigned int i) {
		return ((t_float*)this)[i];
	}

	vec3 vec3::operator+ (const vec3& a) const {
		return vec3(this->x + a.x, this->y + a.y, this->z + a.z);
	}

	vec3 vec3::operator- (const vec3& a) const {
		return vec3(this->x - a.x, this->y - a.y, this->z - a.z);
	}

	vec3 vec3::operator* (t_float a) const {
		return vec3(this->x * a, this->y * a, this->z * a);
	}

	vec3 vec3::operator/ (t_float a) const {
		return vec3(this->x / a, this->y / a, this->z / a);
	}

	void vec3::operator+= (const vec3& a) {
		this->x += a.x;
		this->y += a.y;
		this->z += a.z;
	}

	void vec3::operator-= (const vec3& a) {
		this->x -= a.x;
		this->y -= a.y;
		this->z -= a.z;
	}

	void vec3::operator*= (t_float a) {
		this->x *= a;
		this->y *= a;
		this->z *= a;
	}

	void vec3::operator/= (t_float a) {
		this->x /= a;
		this->y /= a;
		this->z /= a;
	}
	//vec4
	vec4::vec4() : x(0), y(0), z(0), w(0) {}
	vec4::vec4(t_float x, t_float y, t_float z, t_float w) : x(x), y(y), z(z), w(w) {}
	vec4::vec4(t_float v) : x(v), y(v), z(v), w(v) {}
	vec4::vec4(vec2 xy, t_float z, t_float w) : xy(xy), _z(z), _w(w) {}
	vec4::vec4(t_float x, vec2 yz, t_float w) : x(x), y(yz.x), z(yz.y), w(w) {}
	vec4::vec4(t_float x, t_float y, vec2 zw) : x(x), y(y), z(zw.x), w(zw.y) {}
	vec4::vec4(vec3 xyz, t_float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	vec4::vec4(t_float x, vec3 yzw) : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

	t_float vec4::length() {
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
	}

	void vec4::normalize() {
		*this /= this->length();
	}

	vec4 vec4::normalized() {
		return *this / this->length();
	}

	t_float& vec4::operator[] (unsigned int i) {
		return ((t_float*)this)[i];
	}

	vec4 vec4::operator+ (const vec4& a) const {
		return vec4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
	}

	vec4 vec4::operator- (const vec4& a) const {
		return vec4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
	}

	vec4 vec4::operator* (t_float a) const {
		return vec4(this->x * a, this->y * a, this->z * a, this->w * a);
	}

	vec4 vec4::operator/ (t_float a) const {
		return vec4(this->x / a, this->y / a, this->z / a, this->w / a);
	}

	vec4 vec4::operator- () const {
		return vec4(-this->x, -this->y, -this->z, -this->w);
	}

	void vec4::operator+= (const vec4& a) {
		this->x += a.x;
		this->y += a.y;
		this->z += a.z;
		this->w += a.w;
	}

	void vec4::operator-= (const vec4& a) {
		this->x -= a.x;
		this->y -= a.y;
		this->z -= a.z;
		this->w -= a.w;
	}

	void vec4::operator*= (t_float a) {
		this->x *= a;
		this->y *= a;
		this->z *= a;
		this->w *= a;
	}

	void vec4::operator/= (t_float a) {
		this->x /= a;
		this->y /= a;
		this->z /= a;
		this->w /= a;
	}
}
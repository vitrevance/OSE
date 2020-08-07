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

	vec2 vec2::operator+ (const vec2& a) {
		return vec2(this->x + a.x, this->y + a.y);
	}

	vec2 vec2::operator- (const vec2& a) {
		return vec2(this->x + a.x, this->y + a.y);
	}

	vec2 vec2::operator* (t_float a) {
		return vec2(this->x * a, this->y * a);
	}

	vec2 vec2::operator/ (t_float a) {
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

	vec3 vec3::operator+ (const vec3& a) {
		return vec3(this->x + a.x, this->y + a.y, this->z + a.z);
	}

	vec3 vec3::operator- (const vec3& a) {
		return vec3(this->x - a.x, this->y - a.y, this->z - a.z);
	}

	vec3 vec3::operator* (t_float a) {
		return vec3(this->x * a, this->y * a, this->z * a);
	}

	vec3 vec3::operator/ (t_float a) {
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

	vec4 vec4::operator+ (const vec4& a) {
		return vec4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
	}

	vec4 vec4::operator- (const vec4& a) {
		return vec4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
	}

	vec4 vec4::operator* (t_float a) {
		return vec4(this->x * a, this->y * a, this->z * a, this->w * a);
	}

	vec4 vec4::operator/ (t_float a) {
		return vec4(this->x / a, this->y / a, this->z / a, this->w / a);
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
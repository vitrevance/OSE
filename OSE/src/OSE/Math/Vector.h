#ifndef OSE_VECTOR_H
#define OSE_VECTOR_H

#include <OSE/Core.h>

namespace OSE {
	class OSE_API vec2 {
	public:
		t_float x, y;

		vec2();
		vec2(t_float x, t_float y);
		vec2(t_float v);

		t_float length();
		void normalize();
		vec2 normalized();

		t_float& operator[] (unsigned int i);
		vec2 operator+ (const vec2& a);
		vec2 operator- (const vec2& a);
		vec2 operator* (t_float a);
		vec2 operator/ (t_float a);
		void operator+= (const vec2& a);
		void operator-= (const vec2& a);
		void operator*= (t_float a);
		void operator/= (t_float a);
	};

	class OSE_API vec3 {
	public:
		union {
			struct { t_float x, y, z; };
			struct { vec2 xy; t_float _z; };
			struct { t_float _x; vec2 yz; };
		};

		vec3();
		vec3(t_float x, t_float y, t_float z);
		vec3(t_float v);
		vec3(vec2 xy, t_float z);
		vec3(t_float x, vec2 yz);

		t_float length();
		void normalize();
		vec3 normalized();

		t_float& operator[] (unsigned int i);
		vec3 operator+ (const vec3& a);
		vec3 operator- (const vec3& a);
		vec3 operator* (t_float a);
		vec3 operator/ (t_float a);
		void operator+= (const vec3& a);
		void operator-= (const vec3& a);
		void operator*= (t_float a);
		void operator/= (t_float a);
	};

	class OSE_API vec4 {
	public:
		union {
			struct { t_float x, y, z, w; };
			struct { vec2 xy; t_float _z; t_float _w; };
			struct { t_float _x; vec2 yz; t_float _w; };
			struct { t_float _x, _y; vec2 zw; };
			struct { vec3 xyz; t_float _w; };
			struct { t_float _x; vec3 yzw; };
		};

		vec4();
		vec4(t_float x, t_float y, t_float z, t_float w);
		vec4(t_float v);
		vec4(vec2 xy, t_float z, t_float w);
		vec4(t_float x, vec2 yz, t_float w);
		vec4(t_float x, t_float y, vec2 zw);
		vec4(vec3 xyz, t_float w);
		vec4(t_float x, vec3 yzw);

		t_float length();
		void normalize();
		vec4 normalized();

		t_float& operator[] (unsigned int i);
		vec4 operator+ (const vec4& a);
		vec4 operator- (const vec4& a);
		vec4 operator* (t_float a);
		vec4 operator/ (t_float a);
		void operator+= (const vec4& a);
		void operator-= (const vec4& a);
		void operator*= (t_float a);
		void operator/= (t_float a);
	};
}

#endif
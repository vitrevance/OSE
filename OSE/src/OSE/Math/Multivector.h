#ifndef OSE_BIVECTOR_H
#define OSE_BIVECTOR_H

#include <OSE/Math/Vector.h>

namespace OSE {
	class OSE_API Bivector4 {
	public:
		t_float xy, yz, xz, xw, yw, zw;

		Bivector4();
		Bivector4(t_float xy, t_float yz, t_float xz, t_float xw, t_float yw, t_float zw);

		t_float value() const;

		Bivector4 operator+ (const Bivector4& a) const;
		Bivector4 operator- (const Bivector4& a) const;
		Bivector4 operator- () const;
		Bivector4 operator* (t_float a) const;
		void operator+= (const Bivector4& a);

	};

	class OSE_API Trivector4 {
	public:
		t_float xyz, yzw, xyw, xzw;

		Trivector4();
		Trivector4(t_float xyz, t_float yzw, t_float xyw, t_float xzw);

		Trivector4 abs() const;
		t_float value() const;

		Trivector4 operator+ (const Trivector4& a) const;
		Trivector4 operator- (const Trivector4& a) const;
		Trivector4 operator- () const;
		Trivector4 operator* (t_float a) const;
		bool operator== (const Trivector4& a) const;
	};

	class OSE_API Tetravector4 {
	public:
		t_float xyzw;

		Tetravector4();
		Tetravector4(t_float xyzw);

		Tetravector4 operator+ (const Tetravector4& a) const;
		Tetravector4 operator- (const Tetravector4& a) const;
		Tetravector4 operator- () const;
		Tetravector4 operator* (t_float a) const;
	};

	class OSE_API Multivector4 {
	public:
		t_float v0;
		vec4 v1;
		Bivector4 v2;
		Trivector4 v3;
		Tetravector4 v4;

		Multivector4();

		Multivector4 operator+ (const Multivector4& a) const;
		Multivector4 operator- (const Multivector4& a) const;
	};
}

#endif
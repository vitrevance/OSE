#ifndef OSE_VECMATH_H
#define OSE_VECMATH_H

#include <OSE/Math/Vector.hpp>
#include <OSE/Math/Matrix.hpp>
#include <OSE/Math/Multivector.hpp>

#define CONST_PI 3.141592653589793238462643383279502884L

namespace OSE {

vec2 OSE_API operator*(vec2 v, mat<2, 2> m);
vec3 OSE_API operator*(vec3 v, mat<3, 3> m);
vec4 OSE_API operator*(vec4 v, mat<4, 4> m);

vec2 OSE_API operator*(mat<2, 2> m, vec2 v);
vec3 OSE_API operator*(mat<3, 3> m, vec3 v);
vec4 OSE_API operator*(mat<4, 4> m, vec4 v);

vec3 OSE_API operator*(mat<3, 4> m, vec4 v);

vec2 OSE_API operator*(t_float a, const vec2& b);
vec3 OSE_API operator*(t_float a, const vec3& b);
vec4 OSE_API operator*(t_float a, const vec4& b);

vec3 OSE_API cross(const vec3& a, const vec3& b);
vec4 OSE_API cross(const vec4& u, const vec4& v, const vec4& w);
bool OSE_API operator<(const vec4& a, const vec4& b);

t_float OSE_API dot(const vec2& a, const vec2& b);
t_float OSE_API dot(const vec3& a, const vec3& b);
t_float OSE_API dot(const vec4& a, const vec4& b);

t_float OSE_API veccos(const vec2& a, const vec2& b);
t_float OSE_API veccos(const vec3& a, const vec3& b);
t_float OSE_API veccos(const vec4& a, const vec4& b);

mat<4, 4> OSE_API lookAt(vec3 from, vec3 at);

t_float OSE_API toRadians(t_float degrees);

Bivector4 OSE_API operator^(const vec4& a, const vec4& b);
Trivector4 OSE_API operator^(const Bivector4& a, const vec4& b);
Tetravector4 OSE_API operator^(const Trivector4& a, const vec4& b);
Tetravector4 OSE_API operator^(const Bivector4& a, const Bivector4& b);

Multivector4 OSE_API operator*(const vec4& a, const vec4& b);
Multivector4 OSE_API operator*(const Multivector4& a, const vec4& b);
Multivector4 OSE_API operator*(const Multivector4& a, const Multivector4& b);

typedef mat<2, 2> mat2;
typedef mat<3, 3> mat3;
typedef mat<4, 4> mat4;
}  // namespace OSE

#endif
#include <OSE/Math/Vecmath.hpp>

namespace OSE {

vec2 operator*(vec2 v, mat<2, 2> m) {
  vec2 result;
  for (unsigned int col = 0; col < 2; col++) {
    for (unsigned int row = 0; row < 2; row++) {
      result[col] += v[row] * m[row][col];
    }
  }
  return result;
}

vec3 operator*(vec3 v, mat<3, 3> m) {
  vec3 result;
  for (unsigned int col = 0; col < 3; col++) {
    for (unsigned int row = 0; row < 3; row++) {
      result[col] += v[row] * m[row][col];
    }
  }
  return result;
}

vec4 operator*(vec4 v, mat<4, 4> m) {
  vec4 result;
  for (unsigned int col = 0; col < 4; col++) {
    for (unsigned int row = 0; row < 4; row++) {
      result[col] += v[row] * m[row][col];
    }
  }
  return result;
}

vec2 operator*(mat<2, 2> m, vec2 v) {
  vec2 result;
  for (unsigned int row = 0; row < 2; row++) {
    for (unsigned int col = 0; col < 2; col++) {
      result[row] += v[col] * m[row][col];
    }
  }
  return result;
}

vec3 operator*(mat<3, 3> m, vec3 v) {
  vec3 result;
  for (unsigned int row = 0; row < 3; row++) {
    for (unsigned int col = 0; col < 3; col++) {
      result[row] += v[col] * m[row][col];
    }
  }
  return result;
}

vec4 operator*(mat<4, 4> m, vec4 v) {
  vec4 result;
  for (unsigned int row = 0; row < 4; row++) {
    for (unsigned int col = 0; col < 4; col++) {
      result[row] += v[col] * m[row][col];
    }
  }
  return result;
}

vec3 operator*(mat<3, 4> m, vec4 v) {
  vec3 result;
  for (unsigned int row = 0; row < 3; row++) {
    for (unsigned int col = 0; col < 4; col++) {
      result[row] += v[col] * m[row][col];
    }
  }
  return result;
}

vec2 operator*(float a, const vec2& b) {
  return b * a;
}

vec3 operator*(float a, const vec3& b) {
  return b * a;
}

vec4 operator*(float a, const vec4& b) {
  return b * a;
}

vec3 cross(const vec3& a, const vec3& b) {
  return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

vec4 cross(const vec4& u, const vec4& v, const vec4& w) {
  float a = (v.x * w.y) - (v.y * w.x);
  float b = (v.x * w.z) - (v.z * w.x);
  float c = (v.x * w.w) - (v.w * w.x);
  float d = (v.y * w.z) - (v.z * w.y);
  float e = (v.y * w.w) - (v.w * w.y);
  float f = (v.z * w.w) - (v.w * w.z);
  // Calculate the result-vector components.
  vec4 result;
  result.x = (u.y * f) - (u.z * e) + (u.w * d);
  result.y = -(u.x * f) + (u.z * c) - (u.w * b);
  result.z = (u.x * e) - (u.y * c) + (u.w * a);
  result.w = -(u.x * d) + (u.y * b) - (u.z * a);
  return -result;
}

bool operator<(const vec4& a, const vec4& b) {
  return a.x == b.x
             ? (a.y == b.y ? (a.z == b.z ? (a.w < b.w) : a.z < b.z) : a.y < b.y)
             : a.x < b.x;
}

float dot(const vec2& a, const vec2& b) {
  return a.x * b.x + a.y * b.y;
}

float dot(const vec3& a, const vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float dot(const vec4& a, const vec4& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float veccos(const vec2& a, const vec2& b) {
  return (a.x * b.x + a.y + b.y) / a.length() / b.length();
}

float veccos(const vec3& a, const vec3& b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z) / a.length() / b.length();
}

float veccos(const vec4& a, const vec4& b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w) / a.length() /
         b.length();
}

mat<4, 4> lookAt(vec3 from, vec3 at) {
  vec3 zaxis = (at - from).normalized();
  vec3 xaxis = (cross(vec3({0, 1, 0}), zaxis));
  vec3 yaxis = cross(zaxis, xaxis);
  return mat<4, 4>({xaxis.x, yaxis.y, zaxis.z, 0, xaxis.y, yaxis.y, zaxis.y, 0,
                    xaxis.z, yaxis.z, zaxis.z, 0, 0, 0, 0, 1});
}

float toRadians(float degrees) {
  return degrees / 180.0 * CONST_PI;
}

Bivector4 operator^(const vec4& a, const vec4& b) {
  Bivector4 result(a.x * b.y - a.y * b.x, a.y * b.z - a.z * b.y,
                   a.x * b.z - a.z * b.x, a.x * b.w - a.w * b.x,
                   a.y * b.w - a.w * b.y, a.z * b.w - a.w * b.z);
  return result;
}

Trivector4 operator^(const Bivector4& a, const vec4& b) {
  Trivector4 result;
  result.xyz = a.xy * b.z + a.yz * b.x - a.xz * b.y;
  result.yzw = a.yz * b.w + a.zw * b.y - a.yw * b.z;
  result.xyw = a.xy * b.w + a.yw * b.x - a.xw * b.y;
  result.xzw = a.xz * b.w + a.zw * b.x - a.xw * b.z;
  return result;
}

Tetravector4 operator^(const Trivector4& a, const vec4& b) {
  Tetravector4 result;
  result.xyzw = a.xyz * b.w - a.yzw * b.x - a.xyw * b.z + a.xzw * b.y;
  return result;
}

Tetravector4 operator^(const Bivector4& a, const Bivector4& b) {
  Tetravector4 result;
  result.xyzw = a.xy * b.zw + a.yz * b.xw - a.xz * b.yw + a.xw + b.yz -
                a.yw * b.xz + a.zw * b.xy;
  return result;
}

Multivector4 operator*(const vec4& a, const vec4& b) {
  Multivector4 result;
  result.v0 = dot(a, b);
  result.v2 = a ^ b;
  return result;
}

Multivector4 operator*(const Multivector4& a, const vec4& b) {
  /*
  Multivector4 result;
  result.v0 = a.v1.w*b.w + a.v1.x*b.x + a.v1.y*b.y + a.v1.z*b.z;

  result.v1.x = a.v0*b.x + a.v2.xw*b.w + a.v2.xy*b.y + a.v2.xz*b.z;
  result.v1.y = a.v0*b.y - a.v2.xy*b.x + a.v2.yw*b.w + a.v2.yz*b.z;
  result.v1.z = a.v0*b.z - a.v2.xz*b.x - a.v2.yz*b.y + a.v2.zw*b.w;
  result.v1.w = a.v0*b.w - a.v2.xw*b.x - a.v2.yw*b.y - a.v2.zw*b.z;

  result.v2.xy =  a.v1.x*b.y - a.v1.y*b.x + a.v3.xyw*b.w + a.v3.xyz*b.z;
  result.v2.yz =  a.v1.y*b.z - a.v1.z*b.y + a.v3.xyz*b.x + a.v3.yzw*b.w;
  result.v2.xz =  a.v1.x*b.z - a.v1.z*b.x - a.v3.xyz*b.y + a.v3.xzw*b.w;
  result.v2.xw = -a.v1.w*b.x + a.v1.x*b.w - a.v3.xyw*b.y - a.v3.xzw*b.z;
  result.v2.yw = -a.v1.w*b.y + a.v1.y*b.w + a.v3.xyw*b.x - a.v3.yzw*b.z;
  result.v2.zw = -a.v1.w*b.z + a.v1.z*b.w + a.v3.xzw*b.x + a.v3.yzw*b.y;

  result.v3.xyz =  a.v2.xy*b.z - a.v2.xz*b.y + a.v2.yz*b.x + a.v4.xyzw*b.w;
  result.v3.yzw = -a.v2.yw*b.z + a.v2.yz*b.w + a.v2.zw*b.y - a.v4.xyzw*b.x;
  result.v3.xyw = -a.v2.xw*b.y + a.v2.xy*b.w + a.v2.yw*b.x - a.v4.xyzw*b.z;
  result.v3.xzw = -a.v2.xw*b.z + a.v2.xz*b.w + a.v2.zw*b.x + a.v4.xyzw*b.y;

  result.v4.xyzw = -a.v3.xyw*b.z + a.v3.xyz*b.w + a.v3.xzw*b.y - a.v3.yzw*b.x;

  return result;
  */
  Multivector4 m;
  m.v1 = b;
  return a * m;
}

Multivector4 operator*(const Multivector4& a, const Multivector4& b) {
  Multivector4 result;

  result.v0 = a.v0 * b.v0 + a.v1.w * b.v1.w + a.v1.x * b.v1.x +
              a.v1.y * b.v1.y + a.v1.z * b.v1.z - a.v2.xw * b.v2.xw -
              a.v2.xy * b.v2.xy - a.v2.xz * b.v2.xz - a.v2.yw * b.v2.yw -
              a.v2.yz * b.v2.yz - a.v2.zw * b.v2.zw - a.v3.xyw * b.v3.xyw -
              a.v3.xyz * b.v3.xyz - a.v3.xzw * b.v3.xzw - a.v3.yzw * b.v3.yzw +
              a.v4.xyzw * b.v4.xyzw;

  result.v1.x = a.v0 * b.v1.x - a.v1.w * b.v2.xw + a.v1.x * b.v0 -
                a.v1.y * b.v2.xy - a.v1.z * b.v2.xz + a.v2.xw * b.v1.w +
                a.v2.xy * b.v1.y + a.v2.xz * b.v1.z - a.v2.yw * b.v3.xyw -
                a.v2.yz * b.v3.xyz - a.v2.zw * b.v3.xzw - a.v3.xyw * b.v2.yw -
                a.v3.xyz * b.v2.yz - a.v3.xzw * b.v2.zw + a.v3.yzw * b.v4.xyzw -
                a.v4.xyzw * b.v3.yzw;
  result.v1.y = a.v0 * b.v1.y - a.v1.w * b.v2.yw + a.v1.x * b.v2.xy +
                a.v1.y * b.v0 - a.v1.z * b.v2.yz + a.v2.xw * b.v3.xyw -
                a.v2.xy * b.v1.x + a.v2.xz * b.v3.xyz + a.v2.yw * b.v1.w +
                a.v2.yz * b.v1.z - a.v2.zw * b.v3.yzw + a.v3.xyw * b.v2.xw +
                a.v3.xyz * b.v2.xz - a.v3.xzw * b.v4.xyzw - a.v3.yzw * b.v2.zw +
                a.v4.xyzw * b.v3.xzw;
  result.v1.z = a.v0 * b.v1.z - a.v1.w * b.v2.zw + a.v1.x * b.v2.xz +
                a.v1.y * b.v2.yz + a.v1.z * b.v0 + a.v2.xw * b.v3.xzw -
                a.v2.xy * b.v3.xyz - a.v2.xz * b.v1.x + a.v2.yw * b.v3.yzw -
                a.v2.yz * b.v1.y + a.v2.zw * b.v1.w + a.v3.xyw * b.v4.xyzw -
                a.v3.xyz * b.v2.xy + a.v3.xzw * b.v2.xw + a.v3.yzw * b.v2.yw -
                a.v4.xyzw * b.v3.xyw;
  result.v1.w = a.v0 * b.v1.w + a.v1.w * b.v0 + a.v1.x * b.v2.xw +
                a.v1.y * b.v2.yw + a.v1.z * b.v2.zw - a.v2.xw * b.v1.x -
                a.v2.xy * b.v3.xyw - a.v2.xz * b.v3.xzw - a.v2.yw * b.v1.y -
                a.v2.yz * b.v3.yzw - a.v2.zw * b.v1.z - a.v3.xyw * b.v2.xy -
                a.v3.xyz * b.v4.xyzw - a.v3.xzw * b.v2.xz - a.v3.yzw * b.v2.yz +
                a.v4.xyzw * b.v3.xyz;

  result.v2.xy = a.v0 * b.v2.xy + a.v1.w * b.v3.xyw + a.v1.x * b.v1.y -
                 a.v1.y * b.v1.x + a.v1.z * b.v3.xyz - a.v2.xw * b.v2.yw +
                 a.v2.xy * b.v0 - a.v2.xz * b.v2.yz + a.v2.yw * b.v2.xw +
                 a.v2.yz * b.v2.xz - a.v2.zw * b.v4.xyzw + a.v3.xyw * b.v1.w +
                 a.v3.xyz * b.v1.z - a.v3.xzw * b.v3.yzw + a.v3.yzw * b.v3.xzw -
                 a.v4.xyzw * b.v2.zw;
  result.v2.yz = a.v0 * b.v2.yz + a.v1.w * b.v3.yzw + a.v1.x * b.v3.xyz +
                 a.v1.y * b.v1.z - a.v1.z * b.v1.y - a.v2.xw * b.v4.xyzw -
                 a.v2.xy * b.v2.xz + a.v2.xz * b.v2.xy - a.v2.yw * b.v2.zw +
                 a.v2.yz * b.v0 + a.v2.zw * b.v2.yw - a.v3.xyw * b.v3.xzw +
                 a.v3.xyz * b.v1.x + a.v3.xzw * b.v3.xyw + a.v3.yzw * b.v1.w -
                 a.v4.xyzw * b.v2.xw;
  result.v2.xz = a.v0 * b.v2.xz + a.v1.w * b.v3.xzw + a.v1.x * b.v1.z -
                 a.v1.y * b.v3.xyz - a.v1.z * b.v1.x - a.v2.xw * b.v2.zw +
                 a.v2.xy * b.v2.yz + a.v2.xz * b.v0 + a.v2.yw * b.v4.xyzw -
                 a.v2.yz * b.v2.xy + a.v2.zw * b.v2.xw + a.v3.xyw * b.v3.yzw -
                 a.v3.xyz * b.v1.y + a.v3.xzw * b.v1.w - a.v3.yzw * b.v3.xyw +
                 a.v4.xyzw * b.v2.yw;
  result.v2.xw = a.v0 * b.v2.xw - a.v1.w * b.v1.x + a.v1.x * b.v1.w -
                 a.v1.y * b.v3.xyw - a.v1.z * b.v3.xzw + a.v2.xw * b.v0 +
                 a.v2.xy * b.v2.yw + a.v2.xz * b.v2.zw - a.v2.yw * b.v2.xy -
                 a.v2.yz * b.v4.xyzw - a.v2.zw * b.v2.xz - a.v3.xyw * b.v1.y -
                 a.v3.xyz * b.v3.yzw - a.v3.xzw * b.v1.z + a.v3.yzw * b.v3.xyz -
                 a.v4.xyzw * b.v2.yz;
  result.v2.yw = a.v0 * b.v2.yw - a.v1.w * b.v1.y + a.v1.x * b.v3.xyw +
                 a.v1.y * b.v1.w - a.v1.z * b.v3.yzw + a.v2.xw * b.v2.xy -
                 a.v2.xy * b.v2.xw + a.v2.xz * b.v4.xyzw + a.v2.yw * b.v0 +
                 a.v2.yz * b.v2.zw - a.v2.zw * b.v2.yz + a.v3.xyw * b.v1.x +
                 a.v3.xyz * b.v3.xzw - a.v3.xzw * b.v3.xyz - a.v3.yzw * b.v1.z +
                 a.v4.xyzw * b.v2.xz;
  result.v2.zw = a.v0 * b.v2.zw - a.v1.w * b.v1.z + a.v1.x * b.v3.xzw +
                 a.v1.y * b.v3.yzw + a.v1.z * b.v1.w + a.v2.xw * b.v2.xz -
                 a.v2.xy * b.v4.xyzw - a.v2.xz * b.v2.xw + a.v2.yw * b.v2.yz -
                 a.v2.yz * b.v2.yw + a.v2.zw * b.v0 + a.v3.xyw * b.v3.xyz -
                 a.v3.xyz * b.v3.xyw + a.v3.xzw * b.v1.x + a.v3.yzw * b.v1.y -
                 a.v4.xyzw * b.v2.xy;

  result.v3.xyz = a.v0 * b.v3.xyz - a.v1.w * b.v4.xyzw + a.v1.x * b.v2.yz -
                  a.v1.y * b.v2.xz + a.v1.z * b.v2.xy + a.v2.xw * b.v3.yzw +
                  a.v2.xy * b.v1.z - a.v2.xz * b.v1.y - a.v2.yw * b.v3.xzw +
                  a.v2.yz * b.v1.x + a.v2.zw * b.v3.xyw - a.v3.xyw * b.v2.zw +
                  a.v3.xyz * b.v0 + a.v3.xzw * b.v2.yw - a.v3.yzw * b.v2.xw +
                  a.v4.xyzw * b.v1.w;
  result.v3.yzw = a.v0 * b.v3.yzw + a.v1.w * b.v2.yz + a.v1.x * b.v4.xyzw +
                  a.v1.y * b.v2.zw - a.v1.z * b.v2.yw - a.v2.xw * b.v3.xyz -
                  a.v2.xy * b.v3.xzw + a.v2.xz * b.v3.xyw - a.v2.yw * b.v1.z +
                  a.v2.yz * b.v1.w + a.v2.zw * b.v1.y - a.v3.xyw * b.v2.xz +
                  a.v3.xyz * b.v2.xw + a.v3.xzw * b.v2.xy + a.v3.yzw * b.v0 -
                  a.v4.xyzw * b.v1.x;
  result.v3.xyw = a.v0 * b.v3.xyw + a.v1.w * b.v2.xy + a.v1.x * b.v2.yw -
                  a.v1.y * b.v2.xw + a.v1.z * b.v4.xyzw - a.v2.xw * b.v1.y +
                  a.v2.xy * b.v1.w - a.v2.xz * b.v3.yzw + a.v2.yw * b.v1.x +
                  a.v2.yz * b.v3.xzw - a.v2.zw * b.v3.xyz + a.v3.xyw * b.v0 +
                  a.v3.xyz * b.v2.zw - a.v3.xzw * b.v2.yz + a.v3.yzw * b.v2.xz -
                  a.v4.xyzw * b.v1.z;
  result.v3.xzw = a.v0 * b.v3.xzw + a.v1.w * b.v2.xz + a.v1.x * b.v2.zw -
                  a.v1.y * b.v4.xyzw - a.v1.z * b.v2.xw - a.v2.xw * b.v1.z +
                  a.v2.xy * b.v3.yzw + a.v2.xz * b.v1.w + a.v2.yw * b.v3.xyz -
                  a.v2.yz * b.v3.xyw + a.v2.zw * b.v1.x + a.v3.xyw * b.v2.yz -
                  a.v3.xyz * b.v2.yw + a.v3.xzw * b.v0 - a.v3.yzw * b.v2.xy +
                  a.v4.xyzw * b.v1.y;

  result.v4.xyzw = a.v0 * b.v4.xyzw - a.v1.w * b.v3.xyz + a.v1.x * b.v3.yzw -
                   a.v1.y * b.v3.xzw + a.v1.z * b.v3.xyw + a.v2.xw * b.v2.yz +
                   a.v2.xy * b.v2.zw - a.v2.xz * b.v2.yw - a.v2.yw * b.v2.xz +
                   a.v2.yz * b.v2.xw + a.v2.zw * b.v2.xy - a.v3.xyw * b.v1.z +
                   a.v3.xyz * b.v1.w + a.v3.xzw * b.v1.y - a.v3.yzw * b.v1.x +
                   a.v4.xyzw * b.v0;

  return result;
}
}  // namespace OSE

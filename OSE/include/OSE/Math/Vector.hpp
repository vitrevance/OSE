#ifndef OSE_VECTOR_H
#define OSE_VECTOR_H

#include <OSE/Core.hpp>

// NOLINTBEGIN

namespace OSE {
template <size_t N>
struct OSE_API vec {
  static_assert(N > 0 && N < 5);
  float coords[N];
};

namespace details {
template <char C>
struct vec_helper {
  template <size_t N>
  static inline constexpr decltype(auto) get(const vec<N>& v) {
    if constexpr (C == 'x')
      return v.x;
    if constexpr (C == 'y')
      return v.y;
    if constexpr (C == 'z')
      return v.z;
    if constexpr (C == 'w')
      return v.w;
  }
};

template <char... chars>
struct extractor {
  template <size_t N>
  inline constexpr auto operator()(const vec<N>& v) {
    static_assert(sizeof...(chars) > 0 && sizeof...(chars) <= 4);
    if constexpr (sizeof...(chars) == 1) {
      return float{vec_helper<chars>::get(v)...};
    } else {
      return vec<sizeof...(chars)>{vec_helper<chars>::get(v)...};
    }
  }
};
}  // namespace details

template <char... chars>
inline consteval auto operator""_vec() {
  return details::extractor<chars...>{};
}

template <>
struct OSE_API vec<2> {
  float x, y;

  vec();
  vec(float x, float y);
  explicit vec(float v);

  float length() const;
  void normalize();
  vec normalized() const;

  float& operator[](unsigned int i);
  vec operator+(const vec& a) const;
  vec operator-(const vec& a) const;
  vec operator*(float a) const;
  vec operator/(float a) const;
  void operator+=(const vec& a);
  void operator-=(const vec& a);
  void operator*=(float a);
  void operator/=(float a);
};

using vec2 = vec<2>;

template <>
struct OSE_API vec<3> {
  float x, y, z;

  vec();
  vec(float x, float y, float z);
  explicit vec(float v);
  vec(vec2 xy, float z);
  vec(float x, vec2 yz);

  float length() const;
  void normalize();
  vec normalized() const;

  float& operator[](unsigned int i);
  vec operator+(const vec& a) const;
  vec operator-(const vec& a) const;
  vec operator*(float a) const;
  vec operator/(float a) const;
  void operator+=(const vec& a);
  void operator-=(const vec& a);
  void operator*=(float a);
  void operator/=(float a);
};

using vec3 = vec<3>;

template <>
struct OSE_API vec<4> {
  float x, y, z, w;

  vec();
  vec(float x, float y, float z, float w);
  explicit vec(float v);
  vec(vec2 xy, float z, float w);
  vec(float x, vec2 yz, float w);
  vec(float x, float y, vec2 zw);
  vec(vec3 xyz, float w);
  vec(float x, vec3 yzw);

  float length() const;
  void normalize();
  vec normalized() const;

  float& operator[](unsigned int i);
  vec operator+(const vec& a) const;
  vec operator-(const vec& a) const;
  vec operator*(float a) const;
  vec operator/(float a) const;
  vec operator-() const;
  void operator+=(const vec& a);
  void operator-=(const vec& a);
  void operator*=(float a);
  void operator/=(float a);

  inline vec2 xy() {
    return vec2(x, y);
  }

  inline vec2 zw() {
    return vec2(z, w);
  }
};

using vec4 = vec<4>;
}  // namespace OSE

// NOLINTEND

#endif
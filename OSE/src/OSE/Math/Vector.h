#ifndef OSE_VECTOR_H
#define OSE_VECTOR_H

#include <OSE/Core.h>

namespace OSE {
	template<size_t N>
	struct OSE_API vec {
		static_assert(N > 0 && N < 5);
		t_float coords[N];
	};

	namespace details {
		template<char C>
		struct vec_helper {
			template<size_t N>
			static inline constexpr decltype(auto) get(const vec<N>& v) {
				if constexpr (C == 'x') return v.x;
				if constexpr (C == 'y') return v.y;
				if constexpr (C == 'z') return v.z;
				if constexpr (C == 'w') return v.w;
			}
		};

		template<char...chars>
		struct extractor {
			template<size_t N>
			inline constexpr auto operator()(const vec<N>& v) {
				static_assert(sizeof...(chars) > 0 && sizeof...(chars) <= 4);
				if constexpr (sizeof...(chars) == 1) {
					return float{vec_helper<chars>::get(v)...};
				}
				else {
					return vec<sizeof...(chars)>{vec_helper<chars>::get(v)...};
				}
			}
		};
	}

	template<typename charT, charT...chars>
	inline consteval auto operator ""_vec() {
		return details::extractor<chars...>{};
	}

	template<>
	struct OSE_API vec<2> {
		t_float x, y;

		vec();
		vec(t_float x, t_float y);
		explicit vec(t_float v);

		t_float length() const;
		void normalize();
		vec normalized() const;

		t_float& operator[] (unsigned int i);
		vec operator+ (const vec& a) const;
		vec operator- (const vec& a) const;
		vec operator* (t_float a) const;
		vec operator/ (t_float a) const;
		void operator+= (const vec& a);
		void operator-= (const vec& a);
		void operator*= (t_float a);
		void operator/= (t_float a);
	};

	using vec2 = vec<2>;

	template<>
	struct OSE_API vec<3> {
		t_float x, y, z;

		vec();
		vec(t_float x, t_float y, t_float z);
		explicit vec(t_float v);
		vec(vec2 xy, t_float z);
		vec(t_float x, vec2 yz);

		t_float length() const;
		void normalize();
		vec normalized() const;

		t_float& operator[] (unsigned int i);
		vec operator+ (const vec& a) const;
		vec operator- (const vec& a) const;
		vec operator* (t_float a) const;
		vec operator/ (t_float a) const;
		void operator+= (const vec& a);
		void operator-= (const vec& a);
		void operator*= (t_float a);
		void operator/= (t_float a);
	};

	using vec3 = vec<3>;

	template<>
	struct OSE_API vec<4> {
		t_float x, y, z, w;

		vec();
		vec(t_float x, t_float y, t_float z, t_float w);
		explicit vec(t_float v);
		vec(vec2 xy, t_float z, t_float w);
		vec(t_float x, vec2 yz, t_float w);
		vec(t_float x, t_float y, vec2 zw);
		vec(vec3 xyz, t_float w);
		vec(t_float x, vec3 yzw);

		t_float length() const;
		void normalize();
		vec normalized() const;

		t_float& operator[] (unsigned int i);
		vec operator+ (const vec& a) const;
		vec operator- (const vec& a) const;
		vec operator* (t_float a) const;
		vec operator/ (t_float a) const;
		vec operator- () const;
		void operator+= (const vec& a);
		void operator-= (const vec& a);
		void operator*= (t_float a);
		void operator/= (t_float a);

		inline vec2 xy() {
			return vec2(x, y);
		}

		inline vec2 zw() {
			return vec2(z, w);
		}
	};

	using vec4 = vec<4>;
}

#endif
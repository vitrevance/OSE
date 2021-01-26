#include <OSE/Math/Rotor.h>

namespace OSE {

	Rotor4::Rotor4() : v0(1), v4(0) {}

	Rotor4::Rotor4(const vec4& a, const vec4& b) {
		this->v0 = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
		this->v2 = Bivector4(a.x * b.y - a.y * b.x, a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x,
			a.x * b.w - a.w * b.x, a.y * b.w - a.w * b.y, a.z * b.w - a.w * b.z);
		this->v4 = 0;
	}

	Rotor4 Rotor4::reverse() const {
		Rotor4 result;
		result.v2 = -this->v2;
		return result;
	}

	void Rotor4::rotate(const Rotor4& r) {
		*this = r * *this * r.reverse();
	}

	Rotor4 Rotor4::xy(t_float angle) {
		return Rotor4(vec4(1, 0, 0, 0), vec4(cos(angle), sin(angle), 0, 0));
	}

	Rotor4 Rotor4::yz(t_float angle) {
		return Rotor4(vec4(0, 1, 0, 0), vec4(0, cos(angle), sin(angle), 0));
	}

	Rotor4 Rotor4::xz(t_float angle) {
		return Rotor4(vec4(1, 0, 0, 0), vec4(cos(angle), 0, sin(angle), 0));
	}

	Rotor4 Rotor4::xw(t_float angle) {
		return Rotor4(vec4(1, 0, 0, 0), vec4(cos(angle), 0, 0, sin(angle)));
	}

	Rotor4 Rotor4::yw(t_float angle) {
		return Rotor4(vec4(0, 1, 0, 0), vec4(0, cos(angle), 0, sin(angle)));
	}

	Rotor4 Rotor4::zw(t_float angle) {
		return Rotor4(vec4(0, 0, 1, 0), vec4(0, 0, cos(angle), sin(angle)));
	}

	Rotor4 operator* (const Rotor4& a, const Rotor4& b) {
		Rotor4 result;

		result.v0 = a.v0*b.v0 + a.v2.xw*b.v2.xw + a.v2.xy*b.v2.xy + a.v2.xz*b.v2.xz + a.v2.yw*b.v2.yw + a.v2.yz*b.v2.yz + a.v2.zw*b.v2.zw + a.v4*b.v4;

		result.v2.xy = a.v0*b.v2.xy - a.v2.xw*b.v2.yw + a.v2.xy*b.v0 - a.v2.xz*b.v2.yz - a.v2.yw*b.v2.xw - a.v2.yz*b.v2.xz + a.v2.zw*b.v4 + a.v4*b.v2.zw;
		result.v2.yz = a.v0*b.v2.yz + a.v2.xw*b.v4 - a.v2.xy*b.v2.xz - a.v2.xz*b.v2.xy - a.v2.yw*b.v2.zw + a.v2.yz*b.v0 - a.v2.zw*b.v2.yw + a.v4*b.v2.xw;
		result.v2.xz = a.v0*b.v2.xz - a.v2.xw*b.v2.zw + a.v2.xy*b.v2.yz + a.v2.xz*b.v0 - a.v2.yw*b.v4 + a.v2.yz*b.v2.xy - a.v2.zw*b.v2.xw - a.v4*b.v2.yw;
		result.v2.xw = a.v0*b.v2.xw + a.v2.xw*b.v0 + a.v2.xy*b.v2.yw + a.v2.xz*b.v2.zw + a.v2.yw*b.v2.xy + a.v2.yz*b.v4 + a.v2.zw*b.v2.xz + a.v4*b.v2.yz;
		result.v2.yw = a.v0*b.v2.yw - a.v2.xw*b.v2.xy - a.v2.xy*b.v2.xw - a.v2.xz*b.v4 + a.v2.yw*b.v0 + a.v2.yz*b.v2.zw + a.v2.zw*b.v2.yz - a.v4*b.v2.xz;
		result.v2.zw = a.v0*b.v2.zw - a.v2.xw*b.v2.xz + a.v2.xy*b.v4 - a.v2.xz*b.v2.xw - a.v2.yw*b.v2.yz - a.v2.yz*b.v2.yw + a.v2.zw*b.v0 + a.v4*b.v2.xy;

		result.v4 = a.v0*b.v4 + a.v2.xw*b.v2.yz + a.v2.xy*b.v2.zw + a.v2.xz*b.v2.yw + a.v2.yw*b.v2.xz + a.v2.yz*b.v2.xw + a.v2.zw*b.v2.xy + a.v4*b.v0;

		return result;
	}
}
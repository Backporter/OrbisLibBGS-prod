#pragma once

#include <xmmintrin.h>

namespace ConsoleRE
{
	class hkVector4
	{
	public:
		hkVector4() : 
			quad(_mm_set1_ps(0.0f))
		{}

		hkVector4(const float& a_x) :
			quad(_mm_set1_ps(a_x))
		{}

		hkVector4(const float& a_x, const float& a_y, const float& a_z, const float& a_w) : 
			quad(_mm_setr_ps(a_x, a_y, a_z, a_w))
		{}

		hkVector4(const hkVector4& a_rhs) : 
			quad(a_rhs.quad)
		{}

		hkVector4(const __m128& a_rhs) : 
			quad(a_rhs)
		{}

		hkVector4(const NiPoint3& a_point) : 
			quad(_mm_setr_ps(a_point.x, a_point.y, a_point.z, 0.0f))
		{}
	public:
		__m128 quad {};
	};
	static_assert(sizeof(hkVector4) == 0x10);
}
#pragma once

#include <cstdio>
#include <math.h>
#include <cfloat>
#include <assert.h>
#include <memory>

namespace ConsoleRE
{
	class NiPoint2
	{
	public:
		constexpr NiPoint2() noexcept = default;

		constexpr NiPoint2(float a_x, float a_y) noexcept : 
			x(a_x), y(a_y)
		{}

		float& operator[](std::size_t a_idx);
		const float& operator[](std::size_t a_idx) const;
		bool operator==(const NiPoint2& a_rhs) const;
		bool operator!=(const NiPoint2& a_rhs) const;
		NiPoint2 operator+(const NiPoint2& a_rhs) const;
		NiPoint2 operator-(const NiPoint2& a_rhs) const;
		float operator*(const NiPoint2& a_rhs) const;
		NiPoint2 operator*(float a_scalar) const;
		NiPoint2 operator/(float a_scalar) const;
		NiPoint2 operator-() const;
		NiPoint2& operator+=(const NiPoint2& a_rhs);
		NiPoint2& operator-=(const NiPoint2& a_rhs);
		NiPoint2& operator*=(float a_scalar);
		NiPoint2& operator/=(float a_scalar);

		//
		float Cross(const NiPoint2& a_pt) const;
		float Dot(const NiPoint2& a_pt) const;
		float GetDistance(const NiPoint2& a_pt) const noexcept;
		float GetSquaredDistance(const NiPoint2& a_pt) const noexcept;
		float Length() const;
		float SqrLength() const;
		float Unitize();
	public:
		float x { 0.0f };
		float y { 0.0f };
	};
	static_assert(sizeof(NiPoint2) == 0x8);
}
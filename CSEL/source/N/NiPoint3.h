#pragma once

#include <stdio.h>
#include <math.h>
#include <utility>
#include <assert.h>

namespace ConsoleRE
{
	class NiPoint3
	{
	public:
		float& operator[](std::size_t a_idx)
		{
			assert(a_idx < 3);
			return std::addressof(x)[a_idx];
		}

		const float& operator[](std::size_t a_idx) const
		{
			assert(a_idx < 3);
			return std::addressof(x)[a_idx];
		}

		bool operator==(const NiPoint3& a_rhs) const
		{
			return (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z);
		}

		bool operator!=(const NiPoint3& a_rhs) const
		{
			return !operator==(a_rhs);
		}

		NiPoint3 operator+(const NiPoint3& a_rhs) const
		{
			return NiPoint3(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z);
		}

		NiPoint3 operator-(const NiPoint3& a_rhs) const
		{
			return NiPoint3(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z);
		}

		float operator*(const NiPoint3& a_rhs) const
		{
			return x * a_rhs.x + y * a_rhs.y + z * a_rhs.z;
		}

		NiPoint3 operator*(float a_scalar) const
		{
			return NiPoint3(x * a_scalar, y * a_scalar, z * a_scalar);
		}

		NiPoint3 operator/(float a_scalar) const
		{
			return operator*(1.0F / a_scalar);
		}

		NiPoint3 operator-() const
		{
			return NiPoint3(-x, -y, -z);
		}

		NiPoint3& operator+=(const NiPoint3& a_rhs)
		{
			x += a_rhs.x;
			y += a_rhs.y;
			z += a_rhs.z;
			return *this;
		}

		NiPoint3& operator-=(const NiPoint3& a_rhs)
		{
			x -= a_rhs.x;
			y -= a_rhs.y;
			z -= a_rhs.z;
			return *this;
		}

		NiPoint3& operator*=(float a_scalar)
		{
			x *= a_scalar;
			y *= a_scalar;
			z *= a_scalar;
			return *this;
		}

		NiPoint3& operator/=(float a_scalar)
		{
			return operator*=(1.0F / a_scalar);
		}
	public:
		constexpr NiPoint3() { }

		constexpr NiPoint3(float a_x, float a_y, float a_z) noexcept : x(a_x), y(a_y), z(a_z)
		{
		}

		NiPoint3 Cross(const NiPoint3& a_pt) const
		{
			return NiPoint3(y * a_pt.z - z * a_pt.y, z * a_pt.x - x * a_pt.z, x * a_pt.y - y * a_pt.x);
		}

		float Dot(const NiPoint3& a_pt) const
		{
			return x * a_pt.x + y * a_pt.y + z * a_pt.z;
		}

		float GetDistance(const NiPoint3& a_pt) const noexcept
		{
			return sqrtf(GetSquaredDistance(a_pt));
		}

		float GetSquaredDistance(const NiPoint3& a_pt) const noexcept
		{
			const float dx = a_pt.x - x;
			const float dy = a_pt.y - y;
			const float dz = a_pt.z - z;
			return dx * dx + dy * dy + dz * dz;
		}

		float Length() const
		{
			return sqrtf(x * x + y * y + z * z);
		}

		float SqrLength() const
		{
			return x * x + y * y + z * z;
		}

		NiPoint3 UnitCross(const NiPoint3& a_pt) const
		{
			auto cross = Cross(a_pt);
			cross.Unitize();
			return cross;
		}

		float Unitize()
		{
			auto length = Length();
			if (!isnan(length)) 
			{
				operator/=(length);
			}
			else 
			{
				x = 0.0;
				y = 0.0;
				z = 0.0;
				length = 0.0;
			}
			return length;
		}
	public:
		float x { 0.0f };
		float y { 0.0f };
		float z { 0.0f };
	};
}
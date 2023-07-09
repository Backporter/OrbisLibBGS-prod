#pragma once

namespace ConsoleRE
{
	template <typename T>
	class GPoint
	{
	public:
		T x;
		T y;
	};

	using GPointF = GPoint<float>;
	static_assert(sizeof(GPointF) == 0x8);

	using GPointD = GPoint<double>;
	static_assert(sizeof(GPointD) == 0x10);
}
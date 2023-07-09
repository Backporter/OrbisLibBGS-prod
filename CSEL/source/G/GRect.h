#pragma once

namespace ConsoleRE
{
	template <typename T>
	class GRect
	{
	public:
		GRect() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) { }
		GRect(T a_left, T a_top, T a_right, T a_bottom) : left(a_left), top(a_top), right(a_right), bottom(a_bottom) { }
		~GRect() { }
	public:
		T left;
		T top;
		T right;
		T bottom;
	public:
	};

	using GRectF = GRect<float>;
	static_assert(sizeof(GRectF) == 0x10, "GRectF");

	using GRectD = GRect<double>;
	static_assert(sizeof(GRectD) == 0x20, "GRectD");
}
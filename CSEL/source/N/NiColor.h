#pragma once

namespace ConsoleRE
{
	class NiColor
	{
	public:
		NiColor() : m_red(0), m_green(0), m_blue(0) { }
		NiColor(float a_red, float a_green, float a_blue) : m_red(a_red), m_green(a_green), m_blue(a_blue) { }
	public:
		float m_red;
		float m_green;
		float m_blue;
	};

	class NiColorA
	{
	public:
		NiColorA() : m_red(0), m_green(0), m_blue(0), m_alpha(0) { }
		NiColorA(float a_red, float a_green, float a_blue, float a_alpha) : m_red(a_red), m_green(a_green), m_blue(a_blue), m_alpha(a_alpha) { }
	public:
		float m_red;
		float m_green;
		float m_blue;
		float m_alpha;
	};
}
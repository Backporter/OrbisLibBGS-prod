#pragma once

namespace ConsoleRE
{
	class NiFrustum
	{
	public:
		NiFrustum(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far, bool a_ortho) : m_left(a_left), m_right(a_right), m_top(a_top), m_bottom(a_bottom), m_near(a_near), m_far(a_far), m_ortho(a_ortho)
		{}
	public:
		float m_left;
		float m_right;
		float m_top;
		float m_bottom;
		float m_near;
		float m_far;
		bool  m_ortho;
	};
	static_assert(sizeof(NiFrustum) == 0x1C, "");
}
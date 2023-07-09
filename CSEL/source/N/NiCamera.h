#pragma once
#include "../N/NiRect.h"
#include "../N/NiAVObject.h"

namespace ConsoleRE
{
	class NiCamera : public NiAVObject
	{
	public:
		NiCamera();
		virtual ~NiCamera();
	public:
		static bool WorldPtToScreenPt3(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance)
		{
			using func_t = bool(const float a_matrix[4][4], const NiRect<float>& a_port, const NiPoint3& a_point, float& a_xOut, float& a_yOut, float& a_zOut, float a_zeroTolerance);
			Relocation<func_t*> func("", 0xE81D30);
			return func(a_matrix, a_port, a_point, a_xOut, a_yOut, a_zOut, a_zeroTolerance);
		}
	public:
	};
}
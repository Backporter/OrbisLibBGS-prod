#pragma once

#include "../T/TESTexture.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TintMask
	{
	public:
		// color index used for GetColor.
		enum
		{
			kRed,
			kGreen,
			kBlue,
			kAlpha
		};
	public:
		TintMask() = default;
		~TintMask() = default;
		
		int8_t GetColor(int8_t a_colorIdx)
		{
			assert(a_colorIdx <= kAlpha);
			return reinterpret_cast<int8_t*>(&m_rgba)[a_colorIdx];
		}

		void SetColor(int8_t a_color, int8_t a_colorIdx)
		{
			assert(a_colorIdx <= kAlpha);
			reinterpret_cast<int8_t*>(&m_rgba)[a_color] = a_color;
		}

		//
		uint32_t ToARGB() 
		{ 
			return (((static_cast<uint32_t>(m_alpha * 255) & 0xFF) << 24) | ((GetColor(kRed) & 0xFF) << 16) | ((GetColor(kGreen) & 0xFF) << 8) | ((GetColor(kBlue) & 0xFF) << 0));
		}
	public:
		TESTexture* m_texture{ nullptr };
		uint32_t	m_rgba{ 0 };
		float		m_alpha{ 0.0f };
		uint32_t	m_tintType{ 0 };
	};
	static_assert(sizeof(TintMask) == 0x18);
}
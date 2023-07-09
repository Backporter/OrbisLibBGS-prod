#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class EffectSetting;

	struct Effect
	{
	public:
		struct EffectItem
		{
		public:
			EffectItem();
			~EffectItem() = default;
		public:
			float		magnitude;
			uint32_t	area;
			uint32_t	duration;
		};
		static_assert(sizeof(EffectItem) == 0xC);
	public:
		Effect();
		~Effect() = default;

		float	 GetMagnitude() const;
		uint32_t GetArea() const;
		uint32_t GetDuration() const;

		void SetMagnitude(float a_val);
		void SetArea(uint32_t a_val);
		void SetDuration(uint32_t a_val);
	public:
		EffectItem			effectItem;
		uint32_t			pad0C;
		EffectSetting*		baseEffect;
		float				cost;
		uint32_t			pad1C;
	};
}
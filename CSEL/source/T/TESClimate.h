#pragma once

#include "../B/BSTList.h"
#include "../T/TESForm.h"
#include "../T/TESModel.h"
#include "../T/TESTexture.h"
#include "../W/WeatherType.h"

namespace ConsoleRE
{
	class TESClimate : public TESForm
	{
	public:
		struct SkyObjects
		{
			enum SkyObject
			{
				kSun,
				kSunGlare,
				kTotal
			};
		};
		using SkyObject = SkyObjects::SkyObject;
		
		struct Timing
		{
		public:
			enum class MoonPhaseLength
			{
				kPhaseLengthMask = 0x3F,
				kNone = 0,
				kMasser = 1 << 6,
				kSecunda = 1 << 7
			};

			struct Interval
			{
			public:
				uint8_t begin;
				uint8_t end;
			};
			static_assert(sizeof(Interval) == 0x2);
		public:
			Interval	sunrise;
			Interval	sunset;
			uint8_t		volatility;
			uint8_t		moonPhaseLength;
			uint8_t		unk6;
			uint8_t		unk7;
		};
		static_assert(sizeof(Timing) == 0x8);
	public:
		static constexpr int TypeID = 55;
	public:
		~TESClimate() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
	public:
		TESModel                   nightSky;
		BSSimpleList<WeatherType*> weatherList;
		TESTexture                 skyObjects[SkyObjects::kTotal];
		Timing                     timing;
	};
}
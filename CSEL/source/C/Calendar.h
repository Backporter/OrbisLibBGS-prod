#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

namespace ConsoleRE
{
	class TESGlobal;

	class Calendar
	{
	public:
		inline static constexpr uint8_t DAYS_IN_MONTH[] =
		{
			31,  // Morning Star
			28,  // Sun's Dawn
			31,  // First Seed
			30,  // Rain's Hand
			31,  // Second Seed
			30,  // Midyear
			31,  // Sun's Height
			31,  // Last Seed
			30,  // Hearthfire
			31,  // Frostfall
			30,  // Sun's Dusk
			31   // Evening Star
		};

		struct Days
		{
			enum Day
			{
				kSundas,
				kMorndas,
				kTirdas,
				kMiddas,
				kTurdas,
				kFredas,
				kLoredas,
				kTotal
			};
		};
		using Day = Days::Day;

		struct Months
		{
			enum Month
			{
				kMorningStar,
				kSunsDawn,
				kFirstSeed,
				kRainsHand,
				kSecondSeed,
				kMidyear,
				kSunsHeight,
				kLastSeed,
				kHearthfire,
				kFrostfall,
				kSunsDusk,
				kEveningStar,
				kTotal
			};
		};
		using Month = Months::Month;
	public:
		static Calendar* GetSingleton();

		//
		float         GetCurrentGameTime() const;
		float         GetDay() const;
		std::string   GetDayName() const;
		uint32_t	  GetDayOfWeek() const;
		float         GetDaysPassed() const;
		void		  GetTimeDateString(char* a_dest, uint32_t a_max, bool a_showYear) const;
		float         GetHour() const;
		float         GetHoursPassed() const;
		uint32_t	  GetMonth() const;
		std::string   GetMonthName() const;
		std::tm       GetTime() const;
		float         GetTimescale() const;
		uint32_t	  GetYear() const;
	public:
		TESGlobal*    gameYear;
		TESGlobal*    gameMonth;
		TESGlobal*    gameDay;
		TESGlobal*    gameHour;
		TESGlobal*    gameDaysPassed;
		TESGlobal*    timeScale;
		uint32_t	  midnightsPassed;
		float         rawDaysPassed;
	};
	static_assert(sizeof(Calendar) == 0x38);
}
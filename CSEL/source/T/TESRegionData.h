#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class TESForm;

	class TESRegionData
	{
	public:
		enum class Type
		{
			kObjects = 2,
			kWeather = 3,
			kMap = 4,
			kLand = 5,
			kGrass = 6,
			kSound = 7,
			kImposter = 8
		};

		struct DataHeader
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kOverride = 1 << 0
			};
		public:
			uint8_t							flags;
			uint8_t                         unk09;
			uint8_t                         priority;
			uint8_t                         unk0B;
			uint32_t                        unk0C;
		};
		static_assert(sizeof(DataHeader) == 0x8);

		virtual ~TESRegionData();

		// add
		virtual bool				LoadDataHeader(void* a_arg1);
		virtual void				LoadData(TESForm* a_form);
		virtual Type				GetType() const = 0;
		virtual void				ConstructSelf() = 0;
		virtual void				Unk_05(void) = 0;
		virtual void				CopyFrom(TESRegionData* a_src, bool a_copy) = 0;
		virtual bool				IsLoaded() const = 0;
	public:
		DataHeader dataHeader;
	};
	static_assert(sizeof(TESRegionData) == 0x10);
}

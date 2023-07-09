#pragma once

#include "../B/BGSSoundDescriptor.h"
#include "../B/BSTArray.h"
#include "../F/FormTypes.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESCondition;

	class BGSStandardSoundDef : public BGSSoundDescriptor
	{
	public:
		class SoundPlaybackCharacteristics : public BSISoundDescriptor::BSIPlaybackCharacteristics
		{
		public:
			// override (BSIPlaybackCharacteristics)
			uint8_t  GetFrequencyShift() override;
			uint8_t  GetFrequencyVariance() override;
			uint8_t  GetPriority() override;
			uint16_t GetStaticAttenuation() override;
			uint8_t  GetDBVariance() override;
		public:
			uint8_t			  frequencyShift;
			uint8_t			  frequencyVariance;
			uint8_t			  priority;
			uint8_t			  dbVariance;
			uint16_t		  staticAttenuation;
		};
		static_assert(sizeof(SoundPlaybackCharacteristics) == 0x10);

		struct LengthCharacteristics
		{
		public:
			enum class Looping
			{
				kNone = 0,
				kLoop = 1 << 3,
				kEnvelopeFast = 1 << 4,
				kEnvelopeSlow = 1 << 5
			};
		public:
			uint8_t unk0;
			uint8_t	looping;
			uint8_t unk2;
			uint8_t rumbleSendValue;
		};
		static_assert(sizeof(LengthCharacteristics) == 0x4);
	public:
		~BGSStandardSoundDef() override;

		// override (BGSSoundDescriptor)
		void          Unk_02(void) override;
		void          Unk_03(void) override;
		void          InitSound(TESForm* a_src) override;
		bool          LoadSound(TESFile* a_mod) override;
		uint32_t	  GetType() const override;
		void          Unk_07(void) override;
	public:
		BSTArray<void*>				 soundFiles;
		SoundPlaybackCharacteristics soundCharacteristics;
		TESCondition*                conditions;
		BGSSoundOutput*              outputModel;
		LengthCharacteristics        lengthCharacteristics;
		int32_t						 unk4C;
	};
	static_assert(offsetof(BGSStandardSoundDef, soundCharacteristics) == 0x28);
	static_assert(sizeof(BGSStandardSoundDef) == 0x50);
}
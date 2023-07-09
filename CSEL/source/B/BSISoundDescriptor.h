#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSISoundDescriptor
	{
	public:
		class BSIPlaybackCharacteristics
		{
		public:
			virtual ~BSIPlaybackCharacteristics();

			// add
			virtual uint8_t  GetFrequencyShift() = 0;
			virtual uint8_t  GetFrequencyVariance() = 0;
			virtual uint8_t  GetPriority() = 0;
			virtual uint16_t GetStaticAttenuation() = 0;
			virtual uint8_t  GetDBVariance() = 0;
		};
		static_assert(sizeof(BSIPlaybackCharacteristics) == 0x8);
	public:
		virtual ~BSISoundDescriptor();
		
		// add
		virtual void Unk_02() = 0;
		virtual void Unk_03() = 0;
	public:
	};
	static_assert(sizeof(BSISoundDescriptor) == 0x8);
}
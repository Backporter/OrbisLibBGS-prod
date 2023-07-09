#pragma once

#include "../B/BSTArray.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class ReadableStringTable
		{
		public:
			class StringEntry
			{
			public:
				const char*   originalData;
				BSFixedString convertedString;
			};
		public:
			void*                                           unk00;
			BSScrapArray<StringEntry>*                      entries;
			int32_t											indexSize;
		};

		class WritableStringTable
		{
		public:
			void*                                           unk00;
			BSTHashMap<BSFixedString, uint32_t>*			referenceMap;
			int32_t											indexSize;
		};

		class IVMSaveLoadInterface
		{
		public:
			virtual ~IVMSaveLoadInterface();
			
			// add (IVMSaveLoadInterface)
			virtual void Unk_02() = 0;
			virtual void Unk_03() = 0;
			virtual void Unk_04() = 0;
			virtual void Unk_05() = 0;
			virtual void Unk_06() = 0;
			virtual void Unk_07() = 0;
			virtual void Unk_08() = 0;
			virtual void Unk_09() = 0;
			virtual void Unk_10() = 0;
			virtual void Unk_11() = 0;
			virtual void Unk_12() = 0;
			virtual void Unk_13() = 0;
			virtual void Unk_14() = 0;
			virtual void Unk_15() = 0;
			virtual void Unk_16() = 0;
			virtual void Unk_17() = 0;
			virtual void Unk_18() = 0;
			virtual void Unk_19() = 0;
			virtual void Unk_20() = 0;
			virtual void Unk_21() = 0;
			virtual void Unk_22() = 0;
			virtual void Unk_23() = 0;
		private:
		};
	}
}
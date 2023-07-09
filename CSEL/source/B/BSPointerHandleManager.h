#pragma once

#include "../B/BSHandleRefObject.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	template <class T>
	class BSPointerHandleManager
	{
	public:
		struct Entry
		{
		public:
			enum EntryBitfieldConstants : uint32_t
			{
				// kAgeInc = (1 << T::kFreeListBits),	// 0x100000
				// kFreeListMask = kAgeInc - 1,	// 0xFFFFF
				// kInUseBit = kAgeInc << kAgeShift	// 0x4000000
			};
		public:
			uint32_t					 handleEntryBits;
			uint32_t					 pad04;
			NiPointer<BSHandleRefObject> pointer;
		};

		static auto GetHandleEntries()
		{
			REL::Relocation<Entry(*)[0x100000]> entries("", 0x20C7700);
			return *entries
		}
	};
}
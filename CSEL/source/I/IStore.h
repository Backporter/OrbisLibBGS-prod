#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSStorage.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class IStore : public BSStorage
		{
		public:
			~IStore() override;

			// override (BSStorage)
			uint32_t Write(std::size_t a_numBytes, const void* a_bytes) override;

			// add
			virtual bool                 Open(const char* a_fileName) = 0;
			virtual void                 Close(void) = 0;
			virtual const BSFixedString& GetRelPath() = 0;
			virtual bool                 HasOpenFile(void) = 0;
			virtual bool                 FileIsGood(void) = 0;
			virtual void                 Unk_0B(void) = 0;
		public:
		};
		static_assert(sizeof(IStore) == 0x20);
	}
}
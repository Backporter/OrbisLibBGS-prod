#pragma once

#include "../B/BSFixedString.h"
#include "../I/IStore.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace SkyrimScript
	{
		class Store : public BSScript::IStore
		{
		public:
			~Store() override;

			// override (BSScript::IStore)
			size_t						GetSize() const override;
			size_t						GetPosition() const override;
			uint32_t					Seek(size_t a_offset, uint32_t a_seekMode) const override;
			uint32_t					Read(size_t a_numBytes, void* a_bytes) const override;
			bool						Open(const char* a_fileName) override;
			void						Close() override;
			const BSFixedString&		GetRelPath() override;
			bool						HasOpenFile() override;
			bool						FileIsGood() override;
			void						Unk_0B() override;
		public:
			uint64_t			Unk20;
			void*				stream;
			BSFixedString       relPath;
			bool                hasOpenFile;
			bool                fileIsGood;
			uint16_t			Unk3A;
			uint32_t			Unk3C;
			uint64_t			Unk40;
		};
		static_assert(sizeof(Store) == 0x48);
	}
}
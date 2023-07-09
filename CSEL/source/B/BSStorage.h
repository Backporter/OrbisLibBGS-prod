#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	class BSStorage : public BSIntrusiveRefCounted
	{
	public:
		virtual ~BSStorage();

		// add
		virtual size_t GetSize() const = 0;
		virtual size_t GetPosition() const = 0;
		virtual uint32_t Seek(size_t a_offset, uint32_t a_seekMode) const = 0;
		virtual uint32_t Read(size_t a_numBytes, void* a_bytes) const;
		virtual uint32_t Write(size_t a_numBytes, const void* a_bytes);
	public:
		uint32_t Unk0C;
		void*	 Unk10;
		uint64_t Unk18;
	};
	static_assert(sizeof(BSStorage) == 0x20);
}
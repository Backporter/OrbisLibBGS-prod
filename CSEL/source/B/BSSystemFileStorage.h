#pragma once

#include "../B/BSStorage.h"

namespace ConsoleRE
{
	class BSSystemFileStorage : public BSStorage
	{
	public:
		~BSSystemFileStorage() override;

		// override (BSStorage)
		size_t   GetSize() const override;
		size_t   GetPosition() const override;
		uint32_t Seek(size_t a_offset, uint32_t a_seekMode) const override;
		uint32_t Read(size_t a_numBytes, void* a_bytes) const override;
		uint32_t Write(size_t a_numBytes, const void* a_bytes) override;
	public:
	};
}
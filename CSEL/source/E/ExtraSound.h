#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSound>;
	public:
		~ExtraSound();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSoundHandle	phandle;
		uint32_t		pad1C;
	};
	static_assert(sizeof(ExtraSound) == 0x20);
}
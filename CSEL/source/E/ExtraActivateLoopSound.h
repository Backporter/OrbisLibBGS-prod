#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSSoundHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraActivateLoopSound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kActivateLoopSound>;
	public:
		~ExtraActivateLoopSound() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSSoundHandle	handle;
		uint32_t		pad1C;
	};
	static_assert(sizeof(ExtraActivateLoopSound) == 0x20);
}
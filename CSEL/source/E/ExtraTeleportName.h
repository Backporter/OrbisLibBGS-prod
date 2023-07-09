#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSMessage;

	class ExtraTeleportName : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kTeleportName>;
	public:
		~ExtraTeleportName();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSMessage* message;
	};
	static_assert(sizeof(ExtraTeleportName) == 0x18);
}
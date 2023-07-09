#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraObjectHealth : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kObjectHealth>;
	public:
		~ExtraObjectHealth();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		float    health;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraObjectHealth) == 0x18);
}
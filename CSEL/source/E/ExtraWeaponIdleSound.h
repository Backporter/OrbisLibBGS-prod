#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraWeaponIdleSound : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWeaponIdleSound>;
	public:
		~ExtraWeaponIdleSound();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
	};
}
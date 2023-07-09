#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class ExtraRoom : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRoom>;
	public:
		~ExtraRoom();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<BSMultiBoundRoom> room;
	};
	static_assert(sizeof(ExtraRoom) == 0x18);
}
#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class BSPortal;

	class ExtraPortal : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPortal>;
	public:
		~ExtraPortal();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<BSPortal> portal;
	};
	static_assert(sizeof(ExtraPortal) == 0x18);
}
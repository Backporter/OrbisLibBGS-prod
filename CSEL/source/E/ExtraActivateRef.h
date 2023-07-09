#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct REF_ACTIVATE_DATA;

	class ExtraActivateRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kActivateRef>;
	public:
		~ExtraActivateRef() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSSimpleList<REF_ACTIVATE_DATA*> parents;
		uint8_t							 activateFlags;
		uint8_t							 pad21;
		uint16_t						 pad22;
		uint32_t						 pad24;
	};
	static_assert(sizeof(ExtraActivateRef) == 0x28);
}
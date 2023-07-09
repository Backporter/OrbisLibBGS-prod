#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct REF_ACTIVATE_DATA;

	class ExtraActivateRefChildren : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kActivateRefChildren>;
	public:
		~ExtraActivateRefChildren() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<REF_ACTIVATE_DATA*> children;
		float                            activateChildrenTimer;
		uint32_t						 pad24;
	};
	static_assert(sizeof(ExtraActivateRefChildren) == 0x28);
}
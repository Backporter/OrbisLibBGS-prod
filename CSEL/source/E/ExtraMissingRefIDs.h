#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct ActivateParentID
	{
		uint32_t	  refID;
		float         activateDelay;
	};
	static_assert(sizeof(ActivateParentID) == 0x8);

	class ExtraMissingRefIDs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kMissingRefIDs>;
	public:
		~ExtraMissingRefIDs() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		ActivateParentID* unk10;
		uint32_t     	  unk18;
		uint32_t     	  unk1C;
		uint64_t     	  unk20;
	};
	static_assert(sizeof(ExtraMissingRefIDs) == 0x28);
}
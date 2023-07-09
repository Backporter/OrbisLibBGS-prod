#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BGSKeyword;
	class TESObjectREFR;

	class ExtraLinkedRef : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLinkedRef>;

		struct LinkedRef
		{
			BGSKeyword*    keyword;
			TESObjectREFR* refr;
		};
		static_assert(sizeof(LinkedRef) == 0x10);
	public:
		~ExtraLinkedRef() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool	 IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTSmallArray<LinkedRef> linkedRefs;
	};
	static_assert(sizeof(ExtraLinkedRef) == 0x30);
}

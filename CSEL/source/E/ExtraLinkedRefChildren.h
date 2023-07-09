#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSKeyword;

	class ExtraLinkedRefChildren : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLinkedRefChildren>;

		struct LinkedRefChild
		{
			BGSKeyword*     keyword;
			ObjectRefHandle refr;
			uint32_t		pad0C;
		};
		static_assert(sizeof(LinkedRefChild) == 0x10);
	public:
		~ExtraLinkedRefChildren();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTSmallArray<LinkedRefChild> linkedChildren;
	};
	static_assert(sizeof(ExtraLinkedRefChildren) == 0x30);
}
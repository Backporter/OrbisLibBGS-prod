#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESPackage;

	class ExtraPackage : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPackage>;
	public:
		~ExtraPackage();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESPackage*     unk10;
		int32_t			index;
		ObjectRefHandle target;
		bool            actionComplete;
		bool            activated;
		bool            doneOnce;
		uint8_t			unk23;
		uint32_t		unk24;
	};
	static_assert(sizeof(ExtraPackage) == 0x28);
}
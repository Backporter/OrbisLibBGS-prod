#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct RunOncePackage
	{
		TESPackage* package;
		int8_t		day;
		uint8_t		pad09;
		uint16_t	pad0A;
		uint32_t	pad0C;
	};
	static_assert(sizeof(RunOncePackage) == 0x10);

	class ExtraRunOncePacks : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRunOncePacks>;
	public:
		~ExtraRunOncePacks();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<RunOncePackage*>* packages;
	};
	static_assert(sizeof(ExtraRunOncePacks) == 0x18);
}
#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct Crime;

	class ExtraPlayerCrimeList : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPlayerCrimeList>;
	public:
		~ExtraPlayerCrimeList();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSSimpleList<Crime*>* crimes;
	};
	static_assert(sizeof(ExtraPlayerCrimeList) == 0x18);
}
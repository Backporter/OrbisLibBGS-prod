#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ActorPackageData;

	class ExtraPackageData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPackageData>;
	public:
		~ExtraPackageData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		ActorPackageData* actorPackageData;
	};
	static_assert(sizeof(ExtraPackageData) == 0x18);
}
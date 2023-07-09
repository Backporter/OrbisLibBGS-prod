#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraSpawnContainer : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kSpawnContainer>;
	public:
		~ExtraSpawnContainer();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		ObjectRefHandle container;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraSpawnContainer) == 0x18);
}
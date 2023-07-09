#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraResourcesPreload : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kResourcesPreload>;
	public:
		~ExtraResourcesPreload();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		void* unk10;
	};
	static_assert(sizeof(ExtraResourcesPreload) == 0x18);
}
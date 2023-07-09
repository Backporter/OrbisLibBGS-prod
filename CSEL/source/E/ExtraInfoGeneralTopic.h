#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraInfoGeneralTopic : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kInfoGeneralTopic>;
	public:
		~ExtraInfoGeneralTopic();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		void* unk10;
	};
	static_assert(sizeof(ExtraInfoGeneralTopic) == 0x18);
}
#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BipedAnim;

	class ExtraBiped : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kBiped>;
	public:
		~ExtraBiped() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSTSmartPointer<BipedAnim> biped;
	};
	static_assert(sizeof(ExtraBiped) == 0x18);
}
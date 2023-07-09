#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TrespassPackage;

	class ExtraTresPassPackage : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kTresPassPackage>;
	public:
		~ExtraTresPassPackage();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TrespassPackage* pack;
		uint64_t		 unk18;
	};
	static_assert(sizeof(ExtraTresPassPackage) == 0x20);
}
#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class bhkWorld;
	class NiRefObject;

	class ExtraHavok : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHavok>;
	public:
		~ExtraHavok();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<bhkWorld>    world;
		NiPointer<NiRefObject> unk18;
	};
	static_assert(sizeof(ExtraHavok) == 0x20);
}
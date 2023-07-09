#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	class ExtraReferenceHandle : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kReferenceHandle>;
	public:
		ExtraReferenceHandle();
		explicit ExtraReferenceHandle(uint32_t a_containerRef);
		~ExtraReferenceHandle() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool	 IsNotEqual(const BSExtraData* a_rhs) const override;

		//
		TESObjectREFR* GetOriginalReference();
	public:
		uint32_t containerRef;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraReferenceHandle) == 0x18);
}
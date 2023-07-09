#pragma once

#include "../B/BSExtraData.h"

namespace ConsoleRE
{
	class TESForm;

	class ExtraOwnership : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kOwnership>;
	public:
		ExtraOwnership();
		explicit ExtraOwnership(TESForm* a_owner);
 		~ExtraOwnership() override = default;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESForm* owner;
	};
	static_assert(sizeof(ExtraOwnership) == 0x18);
}

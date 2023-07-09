#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraEnableStateParent : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEnableStateParent>;
	public:
		~ExtraEnableStateParent() override;
		
		// override(BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		int8_t		flags;
		uint8_t		pad11;
		uint16_t	pad12;
		uint32_t	parent;
	};
	static_assert(sizeof(ExtraEnableStateParent) == 0x18);
}
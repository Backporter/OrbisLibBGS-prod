#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESObjectCELL;

	class ExtraPersistentCell : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kPersistentCell>;
	public:
		~ExtraPersistentCell();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		TESObjectCELL* persistentCell;
	};
	static_assert(sizeof(ExtraPersistentCell) == 0x18);
}
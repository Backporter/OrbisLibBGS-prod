#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class ExtraEditorRefMoveData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEditorRefMoveData>;
	public:
		~ExtraEditorRefMoveData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPoint3      realAngle;
		NiPoint3      realLocation;
		NiPoint3      oldLocation;
		uint32_t	  pad34;
	};
	static_assert(sizeof(ExtraEditorRefMoveData) == 0x38);
}
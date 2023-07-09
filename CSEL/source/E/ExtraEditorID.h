#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraEditorID : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEditorID>;
	public:
		~ExtraEditorID();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		BSFixedString editorID;
	};
	static_assert(sizeof(ExtraEditorID) == 0x18);
}
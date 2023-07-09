#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class ExtraEditorRef3DData : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kEditorRef3DData>;
	public:
		~ExtraEditorRef3DData();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<NiAVObject> data3D;
		NiPointer<BSLines>    dataBound;
	};
	static_assert(sizeof(ExtraEditorRef3DData) == 0x20);
}
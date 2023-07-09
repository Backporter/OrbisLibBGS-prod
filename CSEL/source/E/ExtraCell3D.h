#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class NiNode;

	class ExtraCell3D : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCell3D>;
	public:
		~ExtraCell3D() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<NiNode> cellNode;
	};
	static_assert(sizeof(ExtraCell3D) == 0x18);
}
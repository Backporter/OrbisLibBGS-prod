#pragma once

#include "../B/BSTriShape.h"
#include "../N/NiColor.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	namespace BSGraphics
	{
		class IndexBuffer;
	}

	class BSShaderProperty;

	class BSMultiIndexTriShape : public BSTriShape
	{
	public:
		~BSMultiIndexTriShape() override;

		// override (BSGeometry)
		const NiRTTI*         GetRTTI() const override;
		NiObject*             CreateClone(NiCloningProcess& a_cloning) override;
		BSMultiIndexTriShape* AsMultiIndexTriShape() override;
	public:
		BSGraphics::IndexBuffer*    altIndexBuffer;
		uint32_t					altPrimCount;
		float						materialProjection[4][4];
		uint32_t					pad1AC;
		NiPointer<BSShaderProperty> additionalShaderProperty;
		uint8_t						useAdditionalTriList;
		uint8_t						pad1B9;
		uint16_t					pad1BA;
		NiColorA                    materialParams;
		float                       materialScale;
		float                       normalDampener;
		uint32_t					unk1D4;
	};
	static_assert(sizeof(BSMultiIndexTriShape) == 0x1D0);
}
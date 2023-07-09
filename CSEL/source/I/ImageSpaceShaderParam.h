#pragma once

#include "../I/ImageSpaceEffectParam.h"
#include "../N/NiTexture.h"
#include "../N/NiSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	// 0x80
	class ImageSpaceShaderParam : public ImageSpaceEffectParam
	{
	public:
		ImageSpaceShaderParam();
		virtual ~ImageSpaceShaderParam();
	public:
		uint64_t							 unk08;
		uint64_t							 unk10;
		uint64_t							 unk18;
		uint64_t							 unk20;
		uint64_t							 unk28;
		void*								 unk30;
		uint64_t							 unk38;
		void*								 unk40;
		uint64_t							 unk48;
		uint8_t								 unk50[0x18]; // NiTObjectArray<NiPointer<NiTexture>> 
		uint8_t								 unk68[0x18]; // NiTPrimitiveArray<uint32_t>			 
	};
	static_assert(sizeof(ImageSpaceShaderParam) == 0x80, "");
}
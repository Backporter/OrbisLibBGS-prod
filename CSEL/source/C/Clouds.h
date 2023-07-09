#pragma once

#include "../N/NiColor.h"
#include "../N/NiSmartPointer.h"
#include "../S/SkyObject.h"

namespace ConsoleRE
{
	class BSGeometry;
	class NiTexture;

	class Clouds : public SkyObject
	{
	public:
		enum { kTotalLayers = 32 };
	public:
		~Clouds() override;

		// override (SkyObject)
		void Unk_03() override;
		void Update(Sky* a_sky, float a_arg2) override;
	public:
		NiPointer<BSGeometry> clouds[kTotalLayers];
		uint64_t			  unk110[kTotalLayers];
		NiPointer<NiTexture>  transTexture[kTotalLayers];
		NiColor               colors[kTotalLayers];
		float                 alphas[kTotalLayers];
		uint16_t			  numLayers;
		bool                  forceUpdate;
		uint8_t				  pad513;
		uint32_t			  pad514;
		uint64_t			  pad520;
	};
	static_assert(sizeof(Clouds) == 0x520);
}
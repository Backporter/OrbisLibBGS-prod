#pragma once

#include "../B/BSTArray.h"
#include "../N/NiColor.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiProperty;

	class BSMaterialObject
	{
	public:
		struct DIRECTIONAL_DATA 
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kSnow = 1 << 0
			};
		public:
			float                                 falloffScale;
			float                                 falloffBias;
			float                                 noiseUVScale;
			float                                 materialUVScale;
			NiPoint3                              ProjectionDir;
			float                                 normalDampener;
			NiColor                               singlePassColor;
			int32_t								  singlePass;
			uint32_t							  flags;
			uint32_t							  unk2C;
		};
		static_assert(sizeof(DIRECTIONAL_DATA) == 0x38);
	public:
		virtual ~BSMaterialObject();
		
		// add
		virtual void EnsureLoaded();
	public:
		DIRECTIONAL_DATA                directionalData;
		BSTArray<NiPointer<NiProperty>> properties;
	};
}
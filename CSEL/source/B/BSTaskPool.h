#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../N/NiAVObject.h"
#include "../B/BGSTextureSet.h"

namespace ConsoleRE
{
	class BSTaskPool
	{
	public:
		BSTaskPool() = delete;
		~BSTaskPool() = delete;

		static BSTaskPool* GetSingleton()
		{
			Relocation<BSTaskPool**> singleton("", 0x3180508);
			return *singleton;
		}

		uint32_t SetNiGeometryTexture(NiAVObject* geom, BGSTextureSet* textureSet)
		{
			using func_t = uint32_t(decltype(this), NiAVObject*, BGSTextureSet*);
			Relocation<func_t*> func("", 0x6C31A0);
			return func(this, geom, textureSet);
		}

		void ProcessQueue()
		{
			using func_t = void(decltype(this));
			Relocation<func_t*> func("", 0x6BF9C0);
			return func(this);
		}
	public:
	};
}
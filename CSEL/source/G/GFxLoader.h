#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../G/GFxStateBag.h"

namespace ConsoleRE
{
	class GFxLoaderImpl;
	class GFxMovieDef;
	class GFxResourceLib;

	class GFxLoader : public GFxStateBag
	{
	public:
		enum LoadConstants : uint32_t
		{
			kLoadAll = 0,
			kLoadWaitCompletion = 1 << 0,
			kLoadWaitFrame1 = 1 << 1,
			kLoadOrdered = 1 << 4,
			kLoadThreadedBinding = 1 << 5,
			kLoadOnThread = 1 << 6,
			kLoadKeepBindData = 1 << 7,
			kLoadImageFiles = 1 << 16,
			kLoadDisableSWF = 1 << 19,
			kLoadDisableImports = 1 << 20,
			kLoadQuietOpen = 1 << 21,
			kLoadDebugHeap = 1 << 28
		};
	public:
		GFxStateBag* GetStateBagImpl() override;
		~GFxLoader() override;
		virtual bool CheckTagLoader(int32_t);

		GFxMovieDef* CreateMovie(const char* a_filename, uint32_t a_loadConstants = 0, size_t a_memoryArena = 0)
		{
			using func_t = GFxMovieDef*(GFxLoader* const, const char*, uint32_t, size_t);
			Relocation<func_t*> func("CreateMovie", 0x115E1D0);
			return func(this, a_filename, a_loadConstants, a_memoryArena);
		}

		GFxLoaderImpl* GetLoaderImpl() { return impl; }
	public:
		GFxLoaderImpl*		impl;
		GFxResourceLib*		strongResourceLib;
		uint32_t			defLoadFlags;
	};
	static_assert(sizeof(GFxLoader) == 0x20);
}
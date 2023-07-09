#pragma once

#include "../G/GFxResource.h"
#include "../G/GFxStateBag.h"
#include "../G/GMemoryHeap.h"
#include "../G/GRect.h"

namespace ConsoleRE
{
	class GFxMovieView;

	class GFxMovieDef : public GFxResource, public GFxStateBag
	{
	public:
		class MemoryContext : public GRefCountBase<MemoryContext, 2>
		{
		public:
			MemoryContext() = delete;
			~MemoryContext() override;  // 00
		};
		static_assert(sizeof(MemoryContext) == 0x10);

		struct MemoryParams
		{
		public:
			MemoryParams(size_t a_memoryArena = 0) : heapLimitMultiplier(0.25f), maxCollectionRoots(std::numeric_limits<uint32_t>::max()), framesBetweenCollections(std::numeric_limits<uint32_t>::max()), pad4C(0)
			{
				desc.arena = a_memoryArena;
			}

		public:
			GMemoryHeap::HeapDesc	 desc;
			float					 heapLimitMultiplier;
			uint32_t				 maxCollectionRoots;
			uint32_t				 framesBetweenCollections;
			uint32_t				 pad4C;
		};
	public:
		// virtual void								 Unk_02();
		virtual uint32_t							 GetVersion();
		virtual uint32_t							 GetLoadingFrame();
		virtual float								 GetWidth() = 0;
		virtual float								 GetHeight() = 0;
		virtual uint32_t							 GetFrameCount() = 0;
		virtual float								 GetFrameRate() = 0;
		virtual GRectF								 GetFrameRect() = 0;
		virtual uint32_t							 GetSWFFlags() = 0;
		virtual const char*							 GetFileURL() = 0;
		virtual void                                 WaitForLoadFinish(bool a_cancel = false) = 0;
		virtual void                                 WaitForFrame(uint32_t a_frame) = 0;
		virtual uint32_t							 GetFileAttributes() = 0;
		virtual uint32_t							 GetMetadata(char* a_buff, uint32_t a_buffSize) = 0;
		virtual GMemoryHeap*						 GetLoadDataHeap() = 0;
		virtual GMemoryHeap*						 GetBindDataHeap() = 0;
		virtual GMemoryHeap*						 GetImageHeap() = 0;
		virtual void*								 GetMovieDataResource() = 0;
		virtual const void*							 GetExporterInfo() = 0;
		virtual void*								 CreateMemoryContext(const char* a_heapName, const void* a_memParams, bool a_debugHeap);
		virtual GFxMovieView*                        CreateInstance(const MemoryParams& a_memParams, bool a_initFirstFrame = true);
		virtual GFxMovieView*                        CreateInstance(int* a_memContext, bool a_initFirstFrame = true);
		virtual void                                 VisitResources(void* a_visitor, uint32_t a_visitMask = 32774);
		virtual void                                 VisitImportedMovies(void* a_visitor);
		virtual void*								 GetResource(const char* a_exportName);

		// we are just invoking a member function so we can just inline?
		GFxMovieView* CreateInstance(bool a_initFirstFrame = true, size_t a_memoryArena = 0)
		{
			MemoryParams params(a_memoryArena);
			return CreateInstance(params, a_initFirstFrame);
		}
	public:
	};
}
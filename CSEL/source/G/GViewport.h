#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GViewport
	{
	public:
		enum Flag
		{
			kNone = 0,
			kIsRenderTexture = 1,
			kAlphaComposite = 2,
			kUseScissorRect = 4,
			kNoSetState = 8,
			kRenderTextureAlpha = kIsRenderTexture | kAlphaComposite
		};
	public:
		GViewport();
		GViewport(const GViewport& a_rhs);
		GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, int32_t a_scLeft, int32_t a_scTop, int32_t a_scW, int32_t a_scH, uint32_t a_flags);
		GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, int32_t a_scLeft, int32_t a_scTop, int32_t a_scW, int32_t a_scH, float a_scale, float a_ratio, uint32_t a_flags);
		GViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, uint32_t a_flags);
	public:
		int32_t  bufferWidth;
		int32_t  bufferHeight;
		int32_t  left;
		int32_t  top;
		int32_t  width;
		int32_t  height;
		int32_t  scissorLeft;
		int32_t  scissorTop;
		int32_t  scissorWidth;
		int32_t  scissorHeight;
		float    scale;
		float    aspectRatio;
		uint32_t flags;
		uint32_t pad34;
	};
	static_assert(sizeof(GViewport) == 0x38);
}
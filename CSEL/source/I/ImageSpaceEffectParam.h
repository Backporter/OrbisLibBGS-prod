#pragma once

namespace ConsoleRE
{
	class ImageSpaceEffectParam
	{
	public:
		virtual ~ImageSpaceEffectParam();
	};
	static_assert(sizeof(ImageSpaceEffectParam) == 0x8);
}
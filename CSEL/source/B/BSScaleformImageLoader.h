#pragma once
#include "../G/GRefCountImplCore.h"

namespace ConsoleRE
{
	class BSScaleformImageLoader : public GRefCountImplCore
	{
	public:
		// 0x11165BA
		static constexpr int Type = 5;

		BSScaleformImageLoader();
		virtual ~BSScaleformImageLoader();

		virtual void Load(const char* url);
	public:

	};
}
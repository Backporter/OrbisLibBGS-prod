#pragma once

#include "../G/GFxMovieRoot.h"
#include "../F/FxDelegateHandler.h"

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		class SmithingMenu : public FxDelegateHandler
		{
		public:
			virtual ~SmithingMenu();
			
			// add
		public:
			void* unk;
			GFxMovieRoot* movie;
		};
		static_assert(offsetof(SmithingMenu, movie) == 0x18);
	}
}
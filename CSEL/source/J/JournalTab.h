#pragma once

#include "../F/FxDelegateHandler.h"
#include "../G/GPtr.h"

namespace ConsoleRE
{
	class GFxMovieView;

	class JournalTab : public FxDelegateHandler
	{
	public:
		~JournalTab() override;
		
		// add
		virtual void Unk_02();
		virtual void Unk_03();
	public:
		GPtr<GFxMovieView> view;
	};
	static_assert(sizeof(JournalTab) == 0x18);
}
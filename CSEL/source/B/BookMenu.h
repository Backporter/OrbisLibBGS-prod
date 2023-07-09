#pragma once

#include "../B/BSTArray.h"
#include "../I/IMenu.h"
#include "../S/SimpleAnimationGraphManagerHolder.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	struct BSAnimationGraphEvent;

	class ImageData;
	class GFxMovieRoot;

	class BookMenu : public IMenu, public SimpleAnimationGraphManagerHolder, public BSTEventSink<BSAnimationGraphEvent>
	{
	public:
		constexpr static inline const char* MENU_NAME = "Book Menu";
	public:
		~BookMenu() override;
		
		// override (IMenu)
		uint32_t			ProcessMessage(UIMessage& a_message) override;
		void				AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		void				PostDisplay() override;
		void				PreDisplay() override;

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent*, BSTEventSource<BSAnimationGraphEvent>*) override;
		
		//
		TESObjectREFR* GetTargetReference();
	public:
		BSTArray<ImageData>		unk50;
		GPtr<GFxMovieView>		book;
		NiPointer<NiAVObject>	book3D;
		uint32_t				unk70;
		uint32_t				pad74;
		uint64_t				unk78;
		void*					unk80;
		uint16_t				unk88;
		uint16_t				unk8A;
		bool					closeMenu;
		bool					isNote;
	};
	static_assert(sizeof(BookMenu) == 0x90);
}
#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTimer.h"
#include "../G/GPtr.h"

namespace ConsoleRE
{
	class GFxMovieView;
	class IMenu;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;

	class UI : public BSTEventSource<MenuOpenCloseEvent>, public BSTEventSource<MenuModeChangeEvent>, public BSTEventSource<void*>
	{
	public:
		using Create_t = IMenu*();

		struct UIMenuEntry
		{
		public:
			GPtr<IMenu>   menu;
			Create_t*	  create;
		};
		static_assert(sizeof(UIMenuEntry) == 0x10);
	
		template <typename T>
		BSTEventSource<T>* GetEventSource();

		template <typename T>
		void				AddEventSource(BSTEventSink<T>* a_eventsource);

		template <typename T>
		void				RemoveEventSource(BSTEventSink<T>* a_eventsource);

		static UI*		    GetSingleton();
		bool			    GameIsPaused();
		GPtr<IMenu>		    GetMenu(const BSFixedString& name);
		GPtr<GFxMovieView>  GetMovieView(const BSFixedString& a_name);
		bool				IsApplicationMenuOpen();
		bool				IsCursorHiddenWhenTopmost();
		bool				IsItemMenuOpen();
		bool				IsMenuOpen(const BSFixedString& a_menuName);
		bool				IsModalMenuOpen();
		bool				IsPauseMenuDisabled();
		bool				IsSavingAllowed();
		bool				IsShowingMenus();
		bool				IsUsingCustomRendering();
		void				Register(const char* a_menuName, Create_t* a_creator);
		void				ShowMenus(bool a_show);
	public:
		BSTArray<GPtr<IMenu>>				   menuStack;
		BSTHashMap<BSFixedString, UIMenuEntry> menuMap;
		mutable BSSpinLock					   processMessagesLock;
		uint32_t							   numPausesGame;
		uint32_t							   numItemMenus;
		uint32_t							   numDisablePauseMenu;
		uint32_t							   numAllowSaving;
		uint32_t							   numDontHideCursorWhenTopmost;
		uint32_t							   numCustomRendering;
		uint32_t							   numApplicationMenus;
		bool								   modal;
		uint8_t								   Unk135;
		uint16_t							   Unk136;
		BSTimer								   uiTimer;
		bool                                   menuSystemVisible;
		bool                                   closingAllMenus;
		uint16_t							   Unk17A;
		uint32_t							   Unk17C;
	};
	static_assert(sizeof(UI) == 0x180);

	template <typename T>
	BSTEventSource<T>* UI::GetEventSource()
	{
		return static_cast<BSTEventSource<T>*>(this);
	}

	template <typename T>
	void UI::AddEventSource(BSTEventSink<T>* a_eventsource)
	{
		GetEventSource<T>()->AddEventSink(a_eventsource);
	}

	template <typename T>
	void UI::RemoveEventSource(BSTEventSink<T>* a_eventsource)
	{
		GetEventSource<T>()->RemoveEventSink(a_eventsource);
	}
}
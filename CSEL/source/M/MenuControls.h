#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTSmartPointer.h"

namespace ConsoleRE
{
	class InputEvent;
	class MenuEventHandler;
	class MenuModeChangeEvent;
	class ClickHandler;
	class ConsoleOpenHandler;
	class DirectionHandler;
	class FavoritesHandler;
	class MenuOpenHandler;
	class QuickSaveLoadHandler;
	class ScreenshotHandler;

	class MenuControls : public BSTEventSink<InputEvent*>, public BSTEventSink<MenuModeChangeEvent>
	{
	public:
		struct QueuedReg
		{
		public:
			QueuedReg(MenuEventHandler* a_handler, bool a_add);
			~QueuedReg() = default;
		public:
			MenuEventHandler* handler;
			bool              add;
			uint8_t			  pad08;
			uint16_t		  pad09;
			uint32_t		  pad0A;
		};
		static_assert(sizeof(QueuedReg) == 0x10);
	public:		
		~MenuControls() override;

		// override (BSTEventSink<InputEvent*>)
		BSEventNotifyControl ProcessEvent(InputEvent* const*, BSTEventSource<InputEvent*>*) override;

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent*, BSTEventSource<MenuModeChangeEvent>*) override;

		static MenuControls* GetSingleton();
	public:
		BSTArray<MenuEventHandler*>           handlers;
		BSTArray<QueuedReg>                   regBuffer;       
		BSTSmartPointer<ClickHandler>		  clickHandler;
		BSTSmartPointer<DirectionHandler>	  directionHandler;
		BSTSmartPointer<ConsoleOpenHandler>	  consoleOpenHandler;
		BSTSmartPointer<QuickSaveLoadHandler> quickSaveLoadHandler;
		BSTSmartPointer<MenuOpenHandler>	  menuOpenHandler;
		BSTSmartPointer<FavoritesHandler>	  favoritesHandler;
		BSTSmartPointer<ScreenshotHandler>	  screenshotHandler;
		bool                                  isProcessing;          
		bool                                  beastForm;             
		bool                                  remapMode;             
		uint8_t								  unk83;                 
		uint32_t							  unk84;                 
	};
	static_assert(sizeof(MenuControls) == 0x70);
}
#pragma once

#include "../../../../../../source/I/IMenu.h"
#include "../../../../../../source/M/MenuEventHandler.h"
#include "../../../../../../source/B/BSScaleformManager.h"
#include "../../../../../../source/F/FxDelegateHandler.h"
#include "../../../../../../source/G/GString.h"
#include "../../../../../../source/B/BSInputDeviceManager.h"

namespace CustomMenu
{
	Relocation<ConsoleRE::FxDelegateHandler::CallbackFn*> PlaySound("", 0xA8B960);

	static std::string swfpath;
	
	class CustomMenu : public ConsoleRE::IMenu
	{
	public:
		static IMenu* Create()
		{
			return new CustomMenu(swfpath.c_str());
		}

		static void SetSWF(const char* path)
		{
			swfpath = path;
		}
	public:
		CustomMenu(const char* path)
		{
			ConsoleRE::BSScaleformManager::GetSingleton()->LoadSFW(this, uiMovie, path, (int)ConsoleRE::GFxMovieView::ScaleModeType::SM_NoBorder, 0.0f);
			
			menuFlags		= 0x11;
			depthPriority	= 0xA;
			inputContext	= 1;
		}
		
		~CustomMenu() override = default;
		
		//
		void Accept(ConsoleRE::FxDelegateHandler::CallbackProcessor* callback) override
		{
			callback->Process("PlaySound", PlaySound.get());
		}
	public:
	};

}
#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class UIMenuStrings
	{
	public:
		static UIMenuStrings* GetSingleton()
		{
			Relocation<UIMenuStrings**> Singletion("", 0x20C4310);
			return *Singletion;
		}
	public:
		BSFixedString	faderData;					// 008 "FaderData"
		BSFixedString	hudData;					// 010 "HUDData"
		BSFixedString	hudCamData;					// 018 "HUDCamData"
		BSFixedString	floatingQuestMarkers;		// 020 "FloatingQuestMarkers"
		BSFixedString	consoleData;				// 028 "ConsoleData"
		BSFixedString	quantityData;				// 030 "QuantityData"
		BSFixedString	messageBoxData;				// 038 "MessageBoxData"
		BSFixedString	bsUIScaleformData;			// 040 "BSUIScaleformData"
		BSFixedString	bsUIMessageData;			// 048 "BSUIMessageData"
		BSFixedString	bsUIAnalogData;				// 050 "BSUIAnalogData"
		BSFixedString	inventoryUpdateData;		// 058 "InventoryUpdateData"
		BSFixedString	refHandleUIData;			// 060 "RefHandleUIData"
		BSFixedString	tesFormUIData;				// 068 "TESFormUIData"
		BSFixedString	loadingMenuData;			// 070 "LoadingMenuData"
		BSFixedString	kinectStateData;			// 078 "KinectStateChangeData"
		BSFixedString	kinectUserEventData;		// 080 "KinectUserEventData"
		BSFixedString	inventoryMenu;				// 088 "InventoryMenu"
		BSFixedString	console;					// 090 "Console"
		BSFixedString	dialogueMenu;				// 098 "Dialogue Menu"
		BSFixedString	hudMenu;					// 0A0 "HUD Menu"
		BSFixedString	mainMenu;					// 0A8 "Main Menu"
		BSFixedString	messageBoxMenu;				// 0B0 "MessageBoxMenu"
		BSFixedString	cursorMenu;					// 0B8 "Cursor Menu"
		BSFixedString	faderMenu;					// 0C0 "Fader Menu"
		BSFixedString	magicMenu;					// 0C8 "MagicMenu"
		BSFixedString	topMenu;					// 0D0 "Top Menu"
		BSFixedString	overlayMenu;				// 0D8 "Overlay Menu"
		BSFixedString	overlayInteractionMenu;		// 0E0 "Overlay Interaction Menu"
		BSFixedString	loadingMenu;				// 0E8 "Loading Menu"
		BSFixedString	tweenMenu;					// 0F0 "TweenMenu"
		BSFixedString	barterMenu;					// 0F8 "BarterMenu"
		BSFixedString	giftMenu;					// 100 "GiftMenu"
		BSFixedString	debugTextMenu;				// 108 "Debug Text Menu"
		BSFixedString	mapMenu;					// 110 "MapMenu"
		BSFixedString	lockpickingMenu;			// 118 "Lockpicking Menu"
		BSFixedString	quantityMenu;				// 120 "Quantity Menu"
		BSFixedString	statsMenu;					// 128 "StatsMenu"
		BSFixedString	containerMenu;				// 130 "ContainerMenu"
		BSFixedString	sleepWaitMenu;				// 138 "Sleep/Wait Menu"
		BSFixedString	levelUpMenu;				// 140 "LevelUp Menu"
		BSFixedString	journalMenu;				// 148 "Journal Menu"
		BSFixedString	bookMenu;					// 150 "Book Menu"
		BSFixedString	favoritesMenu;				// 158 "FavoritesMenu"
		BSFixedString	raceSexMenu;				// 160 "RaceSex Menu"
		BSFixedString	craftingMenu;				// 168 "Crafting Menu"
		BSFixedString	trainingMenu;				// 170 "Training Menu"
		BSFixedString	mistMenu;					// 178 "Mist Menu"
		BSFixedString	tutorialMenu;				// 180 "Tutorial Menu"
		BSFixedString	creditsMenu;				// 188 "Credits Menu"
		BSFixedString	modManagerMenu;				// 190 "Mod Manager Menu"		- NEW IN SE
		BSFixedString	titleSequenceMenu;			// 198 "TitleSequence Menu"
		BSFixedString	consoleNativeUIMenu;		// 1A0 "Console Native UI Menu"
		BSFixedString	kinectMenu;					// 1A8 "Kinect Menu"
		BSFixedString	loadWaitSpinner;			// 1B0 "LoadWaitSpinner"		- NEW IN SE
		BSFixedString	streamingInstallMenu;		// 1B8	"StreamingInstallMenu"  - NEW IN SE
		BSFixedString	textWidget;					// 1C0 "TextWidget"
		BSFixedString	buttonBarWidget;			// 1C8 "ButtonBarWidget"
		BSFixedString	graphWidget;				// 1D0 "GraphWidget"
		BSFixedString	textureWidget;				// 1D8 "TextWidget"
		BSFixedString	uiMenuOK;					// 1E0 "UIMenuOK"
		BSFixedString	uiMenuCancel;				// 1E8 "UIMenuCancel"
		BSFixedString	showText;					// 1F0 "Show Text"
		BSFixedString	hideText;					// 1F8 "Hide Text"
		BSFixedString	showList;					// 200 "Show List"
		BSFixedString	voiceReady;					// 208 "Voice Ready"
		BSFixedString	dmfoStr;					// 210 "DMFOStr"
		BSFixedString	showJournal;				// 218 "Show Journal"
		BSFixedString	journalSettingsSaved;		// 220 "Journal Settings Saved"
		BSFixedString	closeMenu;					// 228 "CloseMenu"
		BSFixedString	closingAllMenus;			// 230 "Closing All Menus"
		BSFixedString	refreshMenu;				// 238 "RefreshMenu"
		BSFixedString	cancelLoading;				// 240 "CancelLoading"		- NEW IN SE
		BSFixedString	menuTextureDegradeEvent;	// 248 "Menu Texture Degrade Event"
		BSFixedString	diamondMarker;				// 250 "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5'>"
	};
}
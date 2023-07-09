#pragma once

#include "../F/FxDelegate.h"
#include "../F/FxDelegateHandler.h"
#include "../G/GFxMovieView.h"
#include "../G/GPtr.h"
#include "../U/UserEvents.h"

namespace ConsoleRE
{
	class CallbackProcessor;
	class UIMessage;

	struct UI_MENU_FLAGS
	{
		enum
		{
			kNone = 0,
			kPausesGame = 1 << 0,
			kAlwaysOpen = 1 << 1,
			kUsesCursor = 1 << 2,
			kUsesMenuContext = 1 << 3,
			kModal = 1 << 4,
			kFreezeFrameBackground = 1 << 5,
			kOnStack = 1 << 6,
			kDisablePauseMenu = 1 << 7,
			kRequiresUpdate = 1 << 8,
			kTopmostRenderedMenu = 1 << 9,
			kUpdateUsesCursor = 1 << 10,
			kAllowSaving = 1 << 11,
			kRendersOffscreenTargets = 1 << 12,
			kInventoryItemMenu = 1 << 13,
			kDontHideCursorWhenTopmost = 1 << 14,
			kCustomRendering = 1 << 15,
			kAssignCursorToRenderer = 1 << 16,
			kApplicationMenu = 1 << 17,
			kHasButtonBar = 1 << 18,
			kIsTopButtonBar = 1 << 19,
			kAdvancesUnderPauseMenu = 1 << 20,
			kRendersUnderPauseMenu = 1 << 21,
			kUsesBlurredBackground = 1 << 22,
			kCompanionAppAllowed = 1 << 23,
			kFreezeFramePause = 1 << 24,
			kSkipRenderDuringFreezeFrameScreenshot = 1 << 25,
			kLargeScaleformRenderCacheMode = 1 << 26,
			kUsesMovementToDirection = 1 << 27
		};
	};

	struct UI_MESSAGE_RESULTS
	{
		enum
		{
			kHandled = 0,
			kIgnore = 1,
			kPassOn = 2
		};
	};

	class IMenu : public FxDelegateHandler
	{
	public:
		using Context = UserEvents::INPUT_CONTEXT_ID;
		using Flag = UI_MENU_FLAGS;
		using AdvanceMovie_t = void(*)(IMenu* const, float, uint32_t);
		using ProcessMessage_t = uint32_t(*)(IMenu* const, UIMessage&);
	public:
		~IMenu() override = default;

		// override (FxDelegateHandler)
		void Accept(CallbackProcessor*) override;

		// add
		virtual void	 PostCreate();
		virtual void	 Unk_04();
		virtual uint32_t ProcessMessage(UIMessage& a_message);
		virtual void	 AdvanceMovie(float, uint32_t a_currentTime);
		virtual void	 PostDisplay();
		virtual void	 PreDisplay();
		virtual void	 RefreshPlatform();
	
		//
		constexpr bool AdvancesUnderPauseMenu()					{ return (menuFlags & Flag::kAdvancesUnderPauseMenu)				== Flag::kAdvancesUnderPauseMenu; }
		constexpr bool AllowSaving()							{ return (menuFlags & Flag::kAllowSaving)							== Flag::kAllowSaving; }
		constexpr bool AlwaysOpen()								{ return (menuFlags & Flag::kAlwaysOpen)							== Flag::kAlwaysOpen; }
		constexpr bool ApplicationMenu()						{ return (menuFlags & Flag::kApplicationMenu)						== Flag::kApplicationMenu; }
		constexpr bool AssignCursorToRenderer()					{ return (menuFlags & Flag::kAssignCursorToRenderer)				== Flag::kAssignCursorToRenderer; }
		constexpr bool CustomRendering()						{ return (menuFlags & Flag::kCustomRendering)						== Flag::kCustomRendering; }
		constexpr bool CompanionAppAllowed()					{ return (menuFlags & Flag::kCompanionAppAllowed)					== Flag::kCompanionAppAllowed; }
		constexpr bool DisablePauseMenu()						{ return (menuFlags & Flag::kDisablePauseMenu)						== Flag::kDisablePauseMenu; }
		constexpr bool DontHideCursorWhenTopmost()				{ return (menuFlags & Flag::kDontHideCursorWhenTopmost)				== Flag::kDontHideCursorWhenTopmost; }
		constexpr bool FreezeFrameBackground()					{ return (menuFlags & Flag::kFreezeFrameBackground)					== Flag::kFreezeFrameBackground; }
		constexpr bool FreezeFramePause()						{ return (menuFlags & Flag::kFreezeFramePause)						== Flag::kFreezeFramePause; }
		constexpr bool HasButtonBar()							{ return (menuFlags & Flag::kHasButtonBar)							== Flag::kHasButtonBar; }
		constexpr bool InventoryItemMenu()						{ return (menuFlags & Flag::kInventoryItemMenu)						== Flag::kInventoryItemMenu; }
		constexpr bool IsTopButtonBar()							{ return (menuFlags & Flag::kIsTopButtonBar)						== Flag::kIsTopButtonBar; }
		constexpr bool LargeScaleformRenderCacheMode()			{ return (menuFlags & Flag::kLargeScaleformRenderCacheMode)			== Flag::kLargeScaleformRenderCacheMode; }
		constexpr bool Modal()									{ return (menuFlags & Flag::kModal)									== Flag::kModal; }
		constexpr bool OnStack()								{ return (menuFlags & Flag::kOnStack)								== Flag::kOnStack; }
		constexpr bool PausesGame()								{ return (menuFlags & Flag::kPausesGame)							== Flag::kPausesGame; }
		constexpr bool RendersOffscreenTargets()				{ return (menuFlags & Flag::kRendersOffscreenTargets)				== Flag::kRendersOffscreenTargets; }
		constexpr bool RendersUnderPauseMenu()					{ return (menuFlags & Flag::kRendersUnderPauseMenu)					== Flag::kRendersUnderPauseMenu; }
		constexpr bool RequiresUpdate()							{ return (menuFlags & Flag::kRequiresUpdate)						== Flag::kRequiresUpdate; }
		constexpr bool SkipRenderDuringFreezeFrameScreenshot()	{ return (menuFlags & Flag::kSkipRenderDuringFreezeFrameScreenshot)	== Flag::kSkipRenderDuringFreezeFrameScreenshot; }
		constexpr bool TopmostRenderedMenu()					{ return (menuFlags & Flag::kTopmostRenderedMenu)					== Flag::kTopmostRenderedMenu; }
		constexpr bool UpdateUsesCursor()						{ return (menuFlags & Flag::kUsesBlurredBackground)					== Flag::kUsesBlurredBackground; }
		constexpr bool UsesBlurredBackground()					{ return (menuFlags & Flag::kUsesCursor)							== Flag::kUsesCursor; }
		constexpr bool UsesCursor()								{ return (menuFlags & Flag::kUsesMenuContext)						== Flag::kUsesMenuContext; }
		constexpr bool UsesMenuContext()						{ return (menuFlags & Flag::kUsesMovementToDirection)				== Flag::kUsesMovementToDirection; }
		constexpr bool UsesMovementToDirection()				{ return (menuFlags & Flag::kUpdateUsesCursor)						== Flag::kUpdateUsesCursor; }
	public:
		GPtr<GFxMovieView>  uiMovie { nullptr };
		uint8_t				depthPriority { 3 };
		uint8_t				Unk19 { 0 };
		uint16_t			Unk1A { 0 };
		uint32_t			menuFlags { Flag::kNone };
		uint32_t			inputContext { Context::kNone };
		GPtr<FxDelegate>	fxDelegate { nullptr };
	};
	static_assert(offsetof(IMenu, uiMovie)		 == 0x10);
	static_assert(offsetof(IMenu, depthPriority) == 0x18);
	static_assert(offsetof(IMenu, Unk19)		 == 0x19);
	static_assert(offsetof(IMenu, Unk1A)		 == 0x1A);
	static_assert(offsetof(IMenu, menuFlags)	 == 0x1C);
	static_assert(offsetof(IMenu, inputContext)	 == 0x20);
	static_assert(offsetof(IMenu, fxDelegate)	 == 0x28);
	static_assert(sizeof(IMenu) == 0x30);
}
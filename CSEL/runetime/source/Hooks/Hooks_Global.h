#pragma once

#include <stdio.h>

namespace Runetime
{
	namespace Hooks
	{
		void ApplyVersionHook();
		void ApplyPapyrusHook();
		void ApplyVMLoadGameHook();
		void ApplyVMReverGameHook();
		void ApplyVMSaveGameHook();
		void ApplyVMFormDeletionHook();
		void ApplySaveGameHistorySaver();
		void ApplyFormLoadHook();

		// this is the default way SKSE does this, the way SKSE does makes it that if a mod doesn't use the build in menu loader function it wont get access to the SKSE addons, given that we don't want this, the newer function hooks the vtble that the default menu loader invokes first, this makes sure it'll get loaded with the addons.
		void ApplyScaleFormHook();
		void ApplyScaleFormHook2();
		void ApplyGFxHook();
		void ApplyPlayerControlsHook();
		void ApplyLogHook();
		void ApplyUIQueue();
		void ApplyEquipmentHook();
		void ApplyRenderTargetHook();
		void ApplyCameraStateHook();
		void ApplyStandardItemDataHook();
		void ApplyMagicItemDataHook();
		void ApplySmithingMenuSetHook();
		void ApplyCraftingSubMenuSetHook();
		void ApplyAlchemyMenuSetHook();
		void ApplyEnchantConstructMenuSetHook();
		void ApplyAlchemyMenuIndexFixUpHook();
		void ApplyItemFavoritesMenuSetHook();
		void ApplyMagicFavoritesMenuSetHook();
		void ApplyVampireFavoritesMenuSetHook();
		void ApplyContainerCategorizationHook();
		void ApplyMapMenuMouseWheelHook();
		void ApplyNewGameHook();
		void ApplySaveGameHook();
		void ApplyLoadGameHook();
		void ApplyDeleteGameHook();
		void ApplySaveQueueProcessorHook();
		void ApplyTaskPoolHook();
		void ApplyHandleHooks();
	}
}
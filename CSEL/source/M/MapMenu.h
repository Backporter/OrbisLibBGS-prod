#pragma once

#include "../B/BSTSmartPointer.h"
#include "../B/BSTEvent.h"
#include "../I/IMenu.h"
#include "../I/IMapCameraCallbacks.h"
#include "../M/MenuOpenCloseEvent.h"
#include "../L/LocalMapMenu.h"
#include "../M/MapLookHandler.h"
#include "../M/MapMoveHandler.h"
#include "../M/MapZoomHandler.h"
#include "../M/MapCamera.h"

namespace ConsoleRE
{
	class BSAudioManager;
	class MenuOpenCloseEvent;
	class TESWorldSpace;

	// 0x30A80
	class MapMenu : public IMenu, public BSTEventSink<MenuOpenCloseEvent>, public IMapCameraCallbacks
	{
	public:
		constexpr static inline const char* MENU_NAME = "MapMenu";

		struct Unk30910
		{
			TESFullName* Unk00;
			uint32_t	 Unk08;
			uint32_t	 Unk0C;
			TESForm*	 Unk10;
		};
	public:
		virtual ~MapMenu();
	public:
		BSTSmartPointer<MapMoveHandler>		moveHandler;
		BSTSmartPointer<MapLookHandler>		lookHandler;
		BSTSmartPointer<MapZoomHandler>		zoomHandler;
		uint8_t								Unk58[0x28];
		LocalMapMenu						Unk80;
		uint64_t							Unk308E0;
		uint64_t							Unk308E8;
		uint64_t							Unk308F0;
		uint64_t							Unk308F8;
		uint32_t							Unk30900;
		uint32_t							Unk30904;
		uint32_t							Unk30908;
		uint32_t							Unk3090C;
		BSTArray<Unk30910>					Unk30910;
		BSTArray<void*>						Unk30920;
		MapCamera							Unk30930;
		uint64_t							Unk309C0;
		TESWorldSpace*						worldSpace;
		GFxValue							Unk309D0;
		uint64_t							Unk309E8;
		uint64_t							Unk309F0;
		uint64_t							Unk309F8;
		uint32_t							Unk30A00;
		uint32_t							Unk30A08;
		uint64_t							Unk30A10;
		uint64_t							Unk30A18;
		uint64_t							Unk30A20;
		uint64_t							Unk30A28;
		uint64_t							Unk30A30;
		uint64_t							Unk30A38;
		uint64_t							Unk30A40;
		uint64_t							Unk30A48;
		uint64_t							Unk30A50;
		uint64_t							Unk30A58;
		uint64_t							Unk30A60;
		uint64_t							Unk30A68;
		uint64_t							Unk30A70;
		uint64_t							Unk30A78;
		uint64_t							Unk30A80;
	};
	static_assert(sizeof(MapMenu) == 0x30A80);
}
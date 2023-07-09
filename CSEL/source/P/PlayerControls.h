#pragma once

#include "../../../OrbisUtil/include//Relocation.h"

#include "../B/BSTEvent.h"
#include "../N/NiPoint2.h"
#include "../M/MovementHandler.h"
#include "../L/LookHandler.h"
#include "../S/SprintHandler.h"
#include "../R/ReadyWeaponHandler.h"
#include "../A/AutoMoveHandler.h"
#include "../T/ToggleRunHandler.h"
#include "../A/ActivateHandler.h"
#include "../J/JumpHandler.h"
#include "../S/ShoutHandler.h"
#include "../A/AttackBlockHandler.h"
#include "../R/RunHandler.h"
#include "../S/SneakHandler.h"
#include "../T/TogglePOVHandler.h"

#include "../P/PlayerControlsData.h"

namespace ConsoleRE
{
	class InputEvent;
	class MenuOpenCloseEvent;
	class MenuModeChangeEvent;
	class TESFurnitureEvent;
	class PlayerInputHandler;

	class PlayerControls : public BSTEventSink<InputEvent*>, public BSTEventSink<MenuOpenCloseEvent>, public BSTEventSink<MenuModeChangeEvent>, public BSTEventSink<TESFurnitureEvent>
	{
	public:
		PlayerControls()			{ _ctor(); }
		virtual ~PlayerControls()	{ _dtor(); }

		static PlayerControls* GetSingleton()
		{
			Relocation<PlayerControls**> Singleton("PlayerControls:Singleton", 0x30CA058);
			return *Singleton;
		}
	private:
		void _ctor()
		{
			using func_t = void(PlayerControls* const);
			Relocation<func_t*> func("", 0x85D400);
			func(this);
		}

		void _dtor()
		{
			using func_t = void(PlayerControls* const);
			Relocation<func_t*> func("", 0x85DC10);
			return func(this);
		}
	public:
		PlayerControlsData			  data;
		BSTArray<PlayerInputHandler*> handlers;
		BSTArray<void*>               unk060;
		BSTArray<void*>               unk070;
		uint8_t						  Unk080[0x10];
		float						  Unk090[0x28];
		BSTArray<uint32_t>			  actionInterestedActor;
		mutable BSSpinLock            actorArrayLock;
		MovementHandler*              movementHandler;
		LookHandler*                  lookHandler;
		SprintHandler*                sprintHandler; 
		ReadyWeaponHandler*           readyWeaponHandler;
		AutoMoveHandler*              autoMoveHandler;
		ToggleRunHandler*             toggleRunHandler;
		ActivateHandler*              activateHandler;
		JumpHandler*                  jumpHandler;
		ShoutHandler*                 shoutHandler;
		AttackBlockHandler*           attackBlockHandler;
		RunHandler*                   runHandler;
		SneakHandler*                 sneakHandler;
		TogglePOVHandler*             togglePOVHandler;
		bool                          notifyingHandlers;
		bool                          blockPlayerInput;
		uint16_t					  unk1DA;
		uint32_t					  unk1DC;
	};
	static_assert(offsetof(PlayerControls, movementHandler) == 0x150, "");
}
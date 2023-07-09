#pragma once

#include "../B/BSSoundHandle.h"
#include "../B/BSTEvent.h"
#include "../I/IMenu.h"
#include "../M/MenuEventHandler.h"
#include "../N/NiMatrix3.h"

namespace ConsoleRE
{
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;
	class TESObjectREFR;

	class LockpickingMenu : 
		public IMenu,
		public MenuEventHandler,
		public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		constexpr static inline const char* MENU_NAME = "Lockpicking Menu";
	public:
		virtual ~LockpickingMenu();

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;
		bool ProcessThumbstick(ThumbstickEvent* a_event) override;
		bool ProcessMouseMove(MouseMoveEvent* a_event) override;
		bool ProcessButton(ButtonEvent* a_event) override;

		TESObjectREFR* GetTargetReference();
	public:
		void*					lockpickShiv;
		void*					lockpick;
		NiMatrix3				unk58;
		NiPoint3				lockRotCenter;
		NiControllerManager*	shivController;
		NiControllerSequence*	shivIntro;
		NiControllerSequence*	shivRotate;
		NiControllerManager*	pickController;
		NiControllerSequence*	pickIntro;
		NiControllerSequence*	pickDamage;
		NiControllerSequence*	pickBreak;
		NiControllerSequence*	currentPickSequence;
		float					pickKeyTime;
		uint32_t				unk0CC;
		NiControllerSequence*	currentShivSequence;
		float					shivKeyTime;
		uint32_t				unk0DC;
		float					currentAngle;
		float					lockAngle;
		uint32_t				unk0E8;
		BSSoundHandle			unk0EC;
		uint32_t				unk0F8;
		uint32_t				unk0FC;
		uint32_t				unk100;
		uint32_t				unk104;
		uint16_t				unk108;
		uint8_t					unk10A;
		uint8_t					unk10B;
		uint8_t					unk10C;
		uint8_t					unk10D;
		uint8_t					unk10E;
		uint8_t					pad10F;
	};
	static_assert(sizeof(LockpickingMenu) == 0x110);
}

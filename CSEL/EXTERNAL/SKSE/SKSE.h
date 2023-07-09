#pragma once

// Headers for game types.
#include "../../source/A/Actor.h"
#include "../../source/B/BSFixedString.h"
#include "../../source/B/BSTEvent.h"
#include "../../source/B/BSTArray.h"
#include "../../source/B/BSAtomic.h"
#include "../../source/B/BowDrawnHandler.h"
#include "../../source/B/BowReleaseHandler.h"
#include "../../source/C/CRC.h"
#include "../../source/I/IHandlerFunctor.h"
#include "../../source/I/IFunctionArguments.h"
#include "../../source/I/IObjectHandlePolicy.h"
#include "../../source/L/LeftHandSpellFireHandler.h"
#include "../../source/L/LeftHandSpellCastHandler.h"
#include "../../source/P/PlayerCamera.h"
#include "../../source/P/PackUnpack.h"
#include "../../source/R/RightHandSpellFireHandler.h"
#include "../../source/R/RightHandSpellCastHandler.h"
#include "../../source/R/RightHandWeaponDrawHandler.h"
#include "../../source/R/RightHandWeaponSheatheHandler.h"
#include "../../source/T/TESObjectREFR.h"
#include "../../source/T/TESForm.h"
#include "../../source/T/TESCameraState.h"
#include "../../source/V/Variable.h"
#include "../../source/V/VirtualMachine.h"
#include "../../source/V/VoiceSpellCastHandler.h"
#include "../../source/V/VoiceSpellFireHandler.h"
#include "../../source/W/WeaponRightSwingHandler.h"
#include "../../source/W/WeaponRightSwingHandler.h"
#include "../../source/W/WeaponBeginDrawRightHandler.h"
#include "../../source/W/WeaponBeginSheatheRightHandler.h"
#include "../../source/W/WeaponLeftSwingHandler.h"

#include <stdint.h>
#include <map>
#include <set>

/*
	- All code here belongs to Ianpatt/SKSE dev team
	- used with explicit permission
*/

namespace SKSE
{
	template <typename D>
	class EventRegistration
	{
	public:
		bool operator<(const EventRegistration & rhs) const { return m_handle < rhs.m_handle; }
	public:
		uint64_t m_handle;
		D		 m_params;
	};
}

// SKSE Types/Structs
namespace SKSE
{
	class ModCallbackParameters
	{
	public:
		ConsoleRE::BSFixedString m_callbackName;
	};

	struct ModCallbackEvent
	{
	public:
		ModCallbackEvent(ConsoleRE::BSFixedString a_eventName, ConsoleRE::BSFixedString a_strArg, float a_numArg, ConsoleRE::TESForm* a_sender) : m_eventName(a_eventName), m_strArg(a_strArg), m_numArg(a_numArg), m_sender(a_sender) { }
	public:
		ConsoleRE::BSFixedString	m_eventName;
		ConsoleRE::BSFixedString	m_strArg;
		float						m_numArg;
		ConsoleRE::TESForm*			m_sender;
	};

	struct CameraEvent
	{
	public:
		CameraEvent(ConsoleRE::TESCameraState* a_oldState, ConsoleRE::TESCameraState* a_newState) : m_oldState(a_oldState), m_newState(a_newState) { }
	public:
		ConsoleRE::TESCameraState* m_oldState;
		ConsoleRE::TESCameraState* m_newState;
	};

	struct CrosshairRefEvent
	{
	public:
		CrosshairRefEvent(ConsoleRE::NiPointer<ConsoleRE::TESObjectREFR>& a_crosshairRef) : m_crosshairRef(a_crosshairRef) { }
	public:
		ConsoleRE::NiPointer<ConsoleRE::TESObjectREFR> m_crosshairRef;
	};

	struct ActionEvent
	{
	public:
		enum
		{
			kType_WeaponSwing = 0,
			kType_SpellCast = 1,
			kType_SpellFire = 2,
			kType_VoiceCast = 3,
			kType_VoiceFire = 4,
			kType_BowDraw = 5,
			kType_BowRelease = 6,
			kType_BeginDraw = 7,
			kType_EndDraw = 8,
			kType_BeginSheathe = 9,
			kType_EndSheathe = 10
		};

		enum
		{
			kSlot_Left = 0,
			kSlot_Right = 1,
			kSlot_Voice = 2
		};
	public:
		ActionEvent(uint32_t a_type, ConsoleRE::Actor * a_actor, ConsoleRE::TESForm * a_source, uint32_t a_slot) : m_type(a_type), m_actor(a_actor), m_sourceForm(a_source), m_slot(a_slot) { }
	public:
		uint32_t				m_type;
		ConsoleRE::Actor*	    m_actor;
		ConsoleRE::TESForm*		m_sourceForm;
		uint32_t				m_slot;
	};

	struct NiNodeUpdateEvent
	{
	public:
		NiNodeUpdateEvent(ConsoleRE::TESObjectREFR* a_reference) : m_reference(a_reference) {}
	public:
		ConsoleRE::TESObjectREFR* m_reference;
	};

	class NullParameters
	{
	public:
	};
}

// Game Linked classes(IFunctionArguments, BSSpinlock)
namespace SKSE
{
	template <typename T1>
	class EventQueueFunctor1 : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		EventQueueFunctor1(const ConsoleRE::BSFixedString& a_eventName, T1 a_arg1) : m_eventName(a_eventName), m_arg1(a_arg1) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(1);

			ConsoleRE::BSScript::PackValue(a_dst->Get(0), m_arg1);

			return true;
		}

		void operator() (const EventRegistration<NullParameters>& reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, m_eventName, this);
		}

	private:
		ConsoleRE::BSFixedString	m_eventName;
		T1							m_arg1;
	};

	template <typename T1, typename T2>
	class EventQueueFunctor2 : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		EventQueueFunctor2(const ConsoleRE::BSFixedString& a_eventName, T1 a_arg1, T2 a_arg2) : m_eventName(a_eventName), m_arg1(a_arg1), m_arg2(a_arg2) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(2);

			ConsoleRE::BSScript::PackValue(a_dst->Get(0), m_arg1);
			ConsoleRE::BSScript::PackValue(a_dst->Get(1), m_arg2);

			return true;
		}

		void operator() (const EventRegistration<NullParameters>& reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, m_eventName, this);
		}

	private:
		ConsoleRE::BSFixedString	m_eventName;
		T1							m_arg1;
		T2							m_arg2;
	};

	template <typename T1, typename T2, typename T3>
	class EventQueueFunctor3 : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		EventQueueFunctor3(const ConsoleRE::BSFixedString& a_eventName, T1 a_arg1, T2 a_arg2, T3 a_arg3) : m_eventName(a_eventName), m_arg1(a_arg1), m_arg2(a_arg2), m_arg3(a_arg3) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(3);

			ConsoleRE::BSScript::PackValue(a_dst->Get(0), m_arg1);
			ConsoleRE::BSScript::PackValue(a_dst->Get(1), m_arg2);
			ConsoleRE::BSScript::PackValue(a_dst->Get(2), m_arg3);

			return true;
		}

		void operator() (const EventRegistration<NullParameters>& reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, m_eventName, this);
		}

	private:
		ConsoleRE::BSFixedString	m_eventName;
		T1							m_arg1;
		T2							m_arg2;
		T3							m_arg3;
	};

	template <typename T1, typename T2, typename T3, typename T4>
	class EventQueueFunctor4 : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		EventQueueFunctor4(const ConsoleRE::BSFixedString& a_eventName, T1 a_arg1, T2 a_arg2, T3 a_arg3, T4 a_arg4) : m_eventName(a_eventName), m_arg1(a_arg1), m_arg2(a_arg2), m_arg3(a_arg3), m_arg4(a_arg4) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(4);

			ConsoleRE::BSScript::PackValue(a_dst->Get(0), m_arg1);
			ConsoleRE::BSScript::PackValue(a_dst->Get(1), m_arg2);
			ConsoleRE::BSScript::PackValue(a_dst->Get(2), m_arg3);
			ConsoleRE::BSScript::PackValue(a_dst->Get(3), m_arg4);

			return true;
		}

		void operator() (const EventRegistration<NullParameters> & reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, m_eventName, this);
		}

	private:
		ConsoleRE::BSFixedString	m_eventName;
		T1							m_arg1;
		T2							m_arg2;
		T3							m_arg3;
		T4							m_arg4;
	};

	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	class EventQueueFunctor5 : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		EventQueueFunctor5(const ConsoleRE::BSFixedString& a_eventName, T1 a_arg1, T2 a_arg2, T3 a_arg3, T4 a_arg4, T5 a_arg5) : m_eventName(a_eventName), m_arg1(a_arg1), m_arg2(a_arg2), m_arg3(a_arg3), m_arg4(a_arg4), m_arg5(a_arg5) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(5);

			ConsoleRE::BSScript::PackValue(a_dst->Get(0), m_arg1);
			ConsoleRE::BSScript::PackValue(a_dst->Get(1), m_arg2);
			ConsoleRE::BSScript::PackValue(a_dst->Get(2), m_arg3);
			ConsoleRE::BSScript::PackValue(a_dst->Get(3), m_arg4);
			ConsoleRE::BSScript::PackValue(a_dst->Get(4), m_arg5);

			return true;
		}

		void operator() (const EventRegistration<NullParameters> & reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, m_eventName, this);
		}

	private:
		ConsoleRE::BSFixedString	m_eventName;
		T1							m_arg1;
		T2							m_arg2;
		T3							m_arg3;
		T4							m_arg4;
		T5							m_arg5;
	};

	class ModCallbackEventFunctor : public ConsoleRE::BSScript::IFunctionArguments
	{
	public:
		ModCallbackEventFunctor(const ConsoleRE::BSFixedString& a_eventName, ConsoleRE::TESForm * a_sender, const ConsoleRE::BSFixedString& a_strArg, float a_numArg) : m_eventName(a_eventName), m_strArg(a_strArg), m_numArg(a_numArg), m_sender(a_sender) { }

		bool Unk_02(ConsoleRE::BSScrapArray<ConsoleRE::BSScript::Variable>* a_dst) override
		{
			a_dst->resize(4);

			a_dst->Get(0)->SetString(m_eventName.c_str());
			a_dst->Get(1)->SetString(m_strArg.c_str());
			a_dst->Get(2)->SetFloat(m_numArg);

			ConsoleRE::BSScript::PackValue(a_dst->Get(3), m_sender);
			return true;
		}

		void operator() (const EventRegistration<ModCallbackParameters> & reg)
		{
			ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->SendEvent(reg.m_handle, reg.m_params.m_callbackName, this);
		}

	private:
		ConsoleRE::BSFixedString   m_eventName;
		ConsoleRE::BSFixedString   m_strArg;
		float					   m_numArg;
		ConsoleRE::TESForm*		   m_sender;
	};

	template <typename T>
	class SafeDataHolder : public ConsoleRE::BSSpinLock
	{
	public:
		T m_T1;
	};
}

// other class stuff
namespace SKSE
{
	template <typename K, typename D = NullParameters>
	class RegistrationMapHolder : public SafeDataHolder<std::map<K, std::set<EventRegistration<D>>>>
	{
	public:
		typedef std::set<EventRegistration<D>>	RegSet;
		typedef std::map<K, RegSet>				RegMap;
	public:
		void Register(K & key, uint64_t handle, D* params = NULL)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = handle;
			if (params)
			{
				reg.params = *params;
			}

			this->Lock();

			if (this->m_T1[key].insert(reg).second)
			{
				policy->PersistHandle(handle);
			}

			this->Unlock();
		}

		template <typename T>
		void Register(K& key, uint32_t type, T* classType, D* params = NULL)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = policy->GetHandleForObject(type, (const void*)classType);
			if (params)
			{
				reg.m_params = *params;
			}

			this->Lock();

			if (this->m_T1[key].insert(reg).second)
			{
				policy->PersistHandle(reg.m_handle);
			}

			this->Unlock();
		}

		void Unregister(K & key, uint64_t handle)
		{
			auto* VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = handle;

			this->Lock();

			if (this->m_T1[key].erase(reg))
			{
				policy->ReleaseHandle(handle);
			}

			this->Unlock();
		}

		template <typename T>
		void Unregister(K & key, uint32_t type, T* classType)
		{
			auto* VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = policy->GetHandleForObject(type, (const void*)classType);

			this->Lock();

			if (this->m_T1[key].erase(reg))
			{
				policy->ReleaseHandle(reg.m_handle);
			}

			this->Unlock();
		}

		void UnregisterAll(uint64_t handle)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = handle;

			this->Lock();

			for (typename RegMap::iterator iter = this->m_T1.begin(); iter != this->m_T1.end(); ++iter)
			{
				if (iter->second.erase(reg))
				{
					policy->ReleaseHandle(handle);
				}
			}

			this->Unlock();
		}

		template <typename T>
		void UnregisterAll(uint32_t type, const T* classType)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = policy->GetHandleForObject(type, (const void*)classType);

			this->Lock();

			for (typename RegMap::iterator iter = this->m_T1.begin(); iter != this->m_T1.end(); ++iter)
			{
				if (iter->second.erase(reg))
				{
					policy->ReleaseHandle(reg.m_handle);
				}
			}

			this->Unlock();
		}

		template <typename F>
		void ForEach(const K& key, F& functor)
		{
			this->Lock();

			typename RegMap::iterator handles = this->m_T1.find(key);

			if (handles != this->m_T1.end())
			{
				for (typename RegSet::iterator iter = handles->second.begin(); iter != handles->second.end(); ++iter)
				{
					functor(*iter);
				}
			}

			this->Unlock();
		}

		void Clear(void)
		{
			this->Lock();
			this->m_T1.clear();
			this->Unlock();
		}
	};

	template <typename D = NullParameters>
	class RegistrationSetHolder : public SafeDataHolder<std::set<EventRegistration<D>>>
	{
		typedef std::set<EventRegistration<D>>	RegSet;
	public:
		void Register(uint64_t handle, D * params = NULL)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = handle;
			if (params)
			{
				reg.params = *params;
			}

			this->Lock();

			if (this->m_T1.insert(reg).second)
			{
				policy->PersistHandle(handle);
			}

			this->Unlock();
		}

		template <typename T>
		void Register(uint32_t type, T* classType, D* params = NULL)
		{
			auto* VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = policy->GetHandleForObject(type, (const void*)classType);
			if (params)
			{
				reg.m_params = *params;
			}

			this->Lock();

			if (this->m_T1.insert(reg).second)
			{
				policy->PersistHandle(reg.m_handle);
			}

			this->Unlock();
		}

		void Unregister(uint64_t handle)
		{
			auto* VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = handle;

			this->Lock();

			if (this->m_T1.erase(reg))
			{
				policy->ReleaseHandle(handle);
			}

			this->Unlock();
		}

		template <typename T>
		void Unregister(uint32_t type, T * classType)
		{
			auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
			auto policy = VM->GetObjectHandlePolicy1();

			EventRegistration<D> reg;
			reg.m_handle = policy->GetHandleForObject(type, (const void*)classType);

			this->Lock();

			if (this->m_T1.erase(reg))
			{
				policy->ReleaseHandle(reg.m_handle);
			}

			this->Unlock();
		}

		template <typename F>
		void ForEach(F & functor)
		{
			this->Lock();

			for (typename RegSet::iterator iter = this->m_T1.begin(); iter != this->m_T1.end(); ++iter)
			{
				functor(*iter);
			}

			this->Unlock();
		}

		void Clear(void)
		{
			this->Lock();
			this->m_T1.clear();
			this->Unlock();
		}
	};
}

// Registration Singletons
namespace SKSE
{
	class ModCallbackRegistrationMapHolder : public RegistrationMapHolder<ConsoleRE::BSFixedString, ModCallbackParameters>
	{
	public:
		static ModCallbackRegistrationMapHolder* GetSingleton()
		{
			static ModCallbackRegistrationMapHolder Singleton;
			return &Singleton;
		}
	};

	class MenuOpenCloseRegistrationMapHolder : public RegistrationMapHolder<ConsoleRE::BSFixedString, NullParameters>
	{
	public:
		static MenuOpenCloseRegistrationMapHolder* GetSingleton()
		{
			static MenuOpenCloseRegistrationMapHolder Singleton;
			return &Singleton;
		}
	};

	class InputKeyEventRegistrationMapHolder : public RegistrationMapHolder<uint32_t>
	{
	public:
		static InputKeyEventRegistrationMapHolder* GetSingleton()
		{
			static InputKeyEventRegistrationMapHolder singleton;
			return &singleton;
		}
	};

	class InputControlRegistrationMapHolder : public RegistrationMapHolder<const ConsoleRE::BSFixedString>
	{
	public:
		static InputControlRegistrationMapHolder* GetSingletion()
		{
			static InputControlRegistrationMapHolder singletion;
			return &singletion;
		}
	};

	class ActionEventRegistrationMapHolder : public RegistrationMapHolder<uint32_t>
	{
	public:
		static ActionEventRegistrationMapHolder* GetSingletion()
		{
			static ActionEventRegistrationMapHolder singletion;
			return &singletion;
		}
	};

	class CameraEventRegistrationSetHolder : public RegistrationSetHolder<NullParameters>
	{
	public:
		static CameraEventRegistrationSetHolder* GetSingletion()
		{
			static CameraEventRegistrationSetHolder singletion;
			return &singletion;
		}
	};

	class CrosshairRefEventRegistrationSetHolder : public RegistrationSetHolder<NullParameters>
	{
	public:
		static CrosshairRefEventRegistrationSetHolder* GetSingletion()
		{
			static CrosshairRefEventRegistrationSetHolder singletion;
			return &singletion;
		}
	};

	class NinodeUpdateRegistrationSetHolder : public RegistrationSetHolder<NullParameters>
	{
	public:
		static NinodeUpdateRegistrationSetHolder* GetSingletion()
		{
			static NinodeUpdateRegistrationSetHolder singletion;
			return &singletion;
		}
	};
}

// Singletons for BSTEventSource<SKSE::T>
namespace SKSE
{
	class CameraEventDispatcher : public ConsoleRE::BSTEventSource<CameraEvent>
	{
	public:
		static CameraEventDispatcher* GetSingleton()
		{
			static CameraEventDispatcher Singleton;
			return &Singleton;
		}
	};

	class CrosshairRefDispatcher : public ConsoleRE::BSTEventSource<CrosshairRefEvent>
	{
	public:
		static CrosshairRefDispatcher* GetSingleton()
		{
			static CrosshairRefDispatcher Singleton;
			return &Singleton;
		}
	};

	class ActionEventDispatcher : public ConsoleRE::BSTEventSource<ActionEvent>
	{
	public:
		static ActionEventDispatcher* GetSingleton()
		{
			static ActionEventDispatcher Singleton;
			return &Singleton;
		}
	};

	class NinodeUpdateDispatcher : public ConsoleRE::BSTEventSource<NiNodeUpdateEvent>
	{
	public:
		static NinodeUpdateDispatcher* GetSingleton()
		{
			static NinodeUpdateDispatcher Singleton;
			return &Singleton;
		}
	};

	class ModCallbackEventDispatcher : public ConsoleRE::BSTEventSource<ModCallbackEvent>
	{
	public:
		static ModCallbackEventDispatcher* GetSingleton()
		{
			static ModCallbackEventDispatcher Singleton;
			return &Singleton;
		}
	};
}

// Singleton/Classes for BSTEventSink<SKSE::T>
namespace SKSE
{
	class ModCallbackEventHandler : public ConsoleRE::BSTEventSink<ModCallbackEvent>
	{
	public:
		static ModCallbackEventHandler* GetSingelton()
		{
			static ModCallbackEventHandler Singleton;
			return &Singleton;
		}

		ConsoleRE::BSEventNotifyControl	ProcessEvent(const ModCallbackEvent* a_event, ConsoleRE::BSTEventSource<ModCallbackEvent>* a_source) override
		{
			if (!a_event)
				return ConsoleRE::BSEventNotifyControl::kContinue;

			ModCallbackEventFunctor mcbef = ModCallbackEventFunctor(a_event->m_eventName, a_event->m_sender, a_event->m_strArg, a_event->m_numArg);
			ModCallbackRegistrationMapHolder::GetSingleton()->ForEach(a_event->m_eventName, mcbef);
			return ConsoleRE::BSEventNotifyControl::kContinue;

		}
	};

	class CameraEventHandler : public ConsoleRE::BSTEventSink<CameraEvent>
	{
	public:
		static CameraEventHandler* GetSingelton()
		{
			static CameraEventHandler Singelton;
			return &Singelton;
		}

		ConsoleRE::BSEventNotifyControl	ProcessEvent(const CameraEvent* evn, ConsoleRE::BSTEventSource<CameraEvent>* dispatcher) override
		{
			int32_t oldState = -1;
			int32_t newState = -1;

			ConsoleRE::PlayerCamera * playerCamera = ConsoleRE::PlayerCamera::GetSingleton();
			if (playerCamera) 
			{
				for (int i = 0; i < 13; i++) 
				{
					if (evn->m_oldState == playerCamera->cameraStates[i].get())
						oldState = i;
					if (evn->m_newState == playerCamera->cameraStates[i].get())
						newState = i;
				}
			}

			ConsoleRE::BSFixedString OPC = ConsoleRE::BSFixedString("OnPlayerCameraState");
			auto EF = EventQueueFunctor2<int32_t, int32_t>(OPC, oldState, newState);
			CameraEventRegistrationSetHolder::GetSingletion()->ForEach(EF);
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};

	class CrosshairRefEventHandler : public ConsoleRE::BSTEventSink<CrosshairRefEvent>
	{
	public:
		static CrosshairRefEventHandler* GetSingelton()
		{
			static CrosshairRefEventHandler Singelton;
			return &Singelton;
		}

		ConsoleRE::BSEventNotifyControl	ProcessEvent(const CrosshairRefEvent* evn, ConsoleRE::BSTEventSource<CrosshairRefEvent>* dispatcher) override
		{
			ConsoleRE::BSFixedString OCHRC = ConsoleRE::BSFixedString("OnCrosshairRefChange");
			auto EQF = EventQueueFunctor1<ConsoleRE::TESObjectREFR*>(OCHRC, evn->m_crosshairRef.get());
			CrosshairRefEventRegistrationSetHolder::GetSingletion()->ForEach(EQF);
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};

	class ActionEventHandler : public ConsoleRE::BSTEventSink <ActionEvent>
	{
	public:
		static ActionEventHandler* GetSingelton()
		{
			static ActionEventHandler Singelton;
			return &Singelton;
		}

		ConsoleRE::BSEventNotifyControl	ProcessEvent(const ActionEvent* evn, ConsoleRE::BSTEventSource<ActionEvent>* dispatcher) override
		{
			ConsoleRE::BSFixedString OAA = ConsoleRE::BSFixedString("OnActorAction");
			auto EQF = EventQueueFunctor4<int32_t, ConsoleRE::Actor*, ConsoleRE::TESForm*, uint32_t>(OAA, evn->m_type, evn->m_actor, evn->m_sourceForm, evn->m_slot);
			ActionEventRegistrationMapHolder::GetSingletion()->ForEach(evn->m_type, EQF);
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};

	class NiNodeUpdateEventHandler : public ConsoleRE::BSTEventSink <NiNodeUpdateEvent>
	{
	public:
		static NiNodeUpdateEventHandler* GetSingelton()
		{
			static NiNodeUpdateEventHandler Singelton;
			return &Singelton;
		}

		ConsoleRE::BSEventNotifyControl	ProcessEvent(const NiNodeUpdateEvent* evn, ConsoleRE::BSTEventSource<NiNodeUpdateEvent>* dispatcher) override
		{
			auto ONINU = ConsoleRE::BSFixedString("OnNiNodeUpdate");
			auto EQF = EventQueueFunctor1<ConsoleRE::TESObjectREFR*>(ONINU, evn->m_reference);
			NinodeUpdateRegistrationSetHolder::GetSingletion()->ForEach(EQF);
			return ConsoleRE::BSEventNotifyControl::kContinue;
		}
	};
}

// Functor, slightly tweaked
namespace SKSE
{
	template <typename T, uint32_t type, uint32_t slot>
	class IHandlerFunctor
	{
	public:
		IHandlerFunctor() = default;
		~IHandlerFunctor() = default;

		// add
		bool Process(ConsoleRE::Actor* a_actor, const ConsoleRE::BSFixedString& a_val)
		{
			ConsoleRE::TESForm* object = slot == ActionEvent::kSlot_Voice ? a_actor->selectedPower : a_actor->GetEquippedObject(slot == ActionEvent::kSlot_Left);
			ActionEvent evn(type, a_actor, object, slot);
			ActionEventDispatcher::GetSingleton()->SendEventSink(&evn);
			return reinterpret_cast<T*>(this)->operator()(a_actor, a_val);
		}
	};
}

// handlers, slightly tweaked.
namespace SKSE
{
	class WeaponRightSwingHandler : public ConsoleRE::WeaponRightSwingHandler, public IHandlerFunctor<ConsoleRE::WeaponRightSwingHandler, 0, 1>
	{
	public:
		WeaponRightSwingHandler() = default;
	public:
		static WeaponRightSwingHandler* get()
		{
			static WeaponRightSwingHandler singleton;
			return &singleton;
		}
	public:
	};

	class WeaponLeftSwingHandler : public ConsoleRE::WeaponLeftSwingHandler, public IHandlerFunctor<ConsoleRE::WeaponLeftSwingHandler, 0, 0>
	{
	public:
		WeaponLeftSwingHandler() = default;
	public:
		static WeaponLeftSwingHandler* get()
		{
			static WeaponLeftSwingHandler singleton;
			return &singleton;
		}
	};

	class RightHandSpellFireHandler : public ConsoleRE::RightHandSpellFireHandler, public IHandlerFunctor<ConsoleRE::RightHandSpellFireHandler, 2, 1>
	{
	public:
		RightHandSpellFireHandler() = default;
	public:
		static RightHandSpellFireHandler* get()
		{
			static RightHandSpellFireHandler singleton;
			return &singleton;
		}
	};

	class LeftHandSpellFireHandler : public ConsoleRE::LeftHandSpellFireHandler, public IHandlerFunctor<ConsoleRE::LeftHandSpellFireHandler, 2, 0>
	{
	public:
		LeftHandSpellFireHandler() = default;
	public:
		static LeftHandSpellFireHandler* get()
		{
			static LeftHandSpellFireHandler singleton;
			return &singleton;
		}
	};

	class RightHandSpellCastHandler : public ConsoleRE::RightHandSpellCastHandler, public IHandlerFunctor<ConsoleRE::RightHandSpellCastHandler, 1, 1>
	{
	public:
		RightHandSpellCastHandler() = default;
	public:
		static RightHandSpellCastHandler* get()
		{
			static RightHandSpellCastHandler singleton;
			return &singleton;
		}
	};

	class LeftHandSpellCastHandler : public ConsoleRE::LeftHandSpellCastHandler, public IHandlerFunctor<ConsoleRE::LeftHandSpellCastHandler, 1, 0>
	{
	public:
		LeftHandSpellCastHandler() = default;
	public:
		static LeftHandSpellCastHandler* get()
		{
			static LeftHandSpellCastHandler singleton;
			return &singleton;
		}
	};

	class VoiceSpellCastHandler : public ConsoleRE::VoiceSpellCastHandler, public IHandlerFunctor<ConsoleRE::VoiceSpellCastHandler, 3, 2>
	{
	public:
		VoiceSpellCastHandler() = default;
	public:
		static VoiceSpellCastHandler* get()
		{
			static VoiceSpellCastHandler singleton;
			return &singleton;
		}
	};

	class VoiceSpellFireHandler : public ConsoleRE::VoiceSpellFireHandler, public IHandlerFunctor<ConsoleRE::VoiceSpellFireHandler, 4, 2>
	{
	public:
		VoiceSpellFireHandler() = default;
	public:
		static VoiceSpellFireHandler* get()
		{
			static VoiceSpellFireHandler singleton;
			return &singleton;
		}
	};

	class BowDrawnHandler : public ConsoleRE::BowDrawnHandler, public IHandlerFunctor<ConsoleRE::BowDrawnHandler, 5, 1>
	{
	public:
		BowDrawnHandler() = default;
	public:
		static BowDrawnHandler* get()
		{
			static BowDrawnHandler singleton;
			return &singleton;
		}

	};

	class BowReleaseHandler : public ConsoleRE::BowReleaseHandler, public IHandlerFunctor<ConsoleRE::BowReleaseHandler, 6, 1>
	{
	public:
		BowReleaseHandler() = default;
	public:
		static BowReleaseHandler* get()
		{
			static BowReleaseHandler singleton;
			return &singleton;
		}
	};

	class WeaponBeginDrawRightHandler : public ConsoleRE::WeaponBeginDrawRightHandler, public IHandlerFunctor<ConsoleRE::WeaponBeginDrawRightHandler, 7, 1>
	{
	public:
		WeaponBeginDrawRightHandler() = default;
	public:
		static WeaponBeginDrawRightHandler* get()
		{
			static WeaponBeginDrawRightHandler singleton;
			return &singleton;
		}
	};

	class WeaponBeginSheatheRightHandler : public ConsoleRE::WeaponBeginSheatheRightHandler, public IHandlerFunctor<ConsoleRE::WeaponBeginSheatheRightHandler, 9, 1>
	{
	public:
		WeaponBeginSheatheRightHandler() = default;
	public:
		static WeaponBeginSheatheRightHandler* get()
		{
			static WeaponBeginSheatheRightHandler singleton;
			return &singleton;
		}
	};

	class RightHandWeaponDrawHandler : public ConsoleRE::RightHandWeaponDrawHandler, public IHandlerFunctor<ConsoleRE::RightHandWeaponDrawHandler, 8, 1>
	{
	public:
		RightHandWeaponDrawHandler() = default;
	public:
		static RightHandWeaponDrawHandler* get()
		{
			static RightHandWeaponDrawHandler singleton;
			return &singleton;
		}
	};

	class RightHandWeaponSheatheHandler : public ConsoleRE::RightHandWeaponSheatheHandler, public IHandlerFunctor<ConsoleRE::RightHandWeaponSheatheHandler, 10, 1>
	{
	public:
		RightHandWeaponSheatheHandler()  = default;
	public:
		static RightHandWeaponSheatheHandler* get()
		{
			static RightHandWeaponSheatheHandler singleton;
			return &singleton;
		}
	};
}
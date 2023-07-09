#include "Misc.h"

#include "../../../../../OrbisUtil/include/FileSystem.h"

#include "../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

namespace Misc
{
	Relocation<void(*)(void*, ConsoleRE::Actor*)> UpdateEquipmentFunction("", 0x77F040);
	
	ConsoleRE::NiPointer<ConsoleRE::TESObjectREFR> g_CrossHairRef;
	
	// inside 0x7E7180, it's been inlined so......
	void SetCrossHairRefr(void*, ConsoleRE::NiPointer<ConsoleRE::TESObjectREFR>* a_crossHairRefr)
	{
	}

	ConsoleRE::TESObjectREFR* GetCrossHairRefr()
	{
		return g_CrossHairRef;
	}

	void PushCrossHairRefEvent()
	{
#if USE_SKSE_ADDON
		SKSE::CrosshairRefEvent evn(g_CrossHairRef);
		SKSE::CrosshairRefDispatcher::GetSingleton()->SendEventSink(&evn);
#endif
	}

	void UpdateEquipment(void* a_this, ConsoleRE::Actor* a_actor)
	{
		UpdateEquipmentFunction(a_this, a_actor);

#if USE_SKSE_ADDON
		SKSE::NiNodeUpdateEvent evn(a_actor);
		SKSE::NinodeUpdateDispatcher::GetSingleton()->SendEventSink(&evn);
#endif
	}

	void PushGlobalCameraEvents(ConsoleRE::TESCameraState* old, ConsoleRE::TESCameraState* current)
	{
#if USE_SKSE_ADDON
		SKSE::CameraEvent m_event(old, current);
		SKSE::CameraEventDispatcher::GetSingleton()->SendEventSink(&m_event);
#endif
	}

	void UpdatecameraState(ConsoleRE::TESCamera* a_this, ConsoleRE::TESCameraState* a_rhs)
	{
		auto s_old = a_this->currentState.get();
		a_this->SetState_Impl(a_rhs);

#if USE_SKSE_ADDON
		PushGlobalCameraEvents(s_old, a_this->currentState.get());
#endif
	}

}
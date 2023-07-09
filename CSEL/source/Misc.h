#pragma once

#include "../../OrbisUtil/include/Relocation.h"

#include "../source/B/BSFixedString.h"

namespace ConsoleRE
{
	class IUIMessageData;

	class Actor;

	template <typename T>
	class NiPointer;

	class TESObjectREFR;

	inline bool	 LookupReferenceByHandle(uint32_t& a_handle, NiPointer<Actor>& a_refOut)
	{
		using func_t = bool(uint32_t&, NiPointer<Actor>&);
		Relocation<func_t*> func("", 0x5DB210);
		return func(a_handle, a_refOut);
	}
	
	inline bool	 LookupReferenceByHandle(uint32_t& a_handle, NiPointer<TESObjectREFR>& a_refOut)
	{
		using func_t = bool(uint32_t&, NiPointer<TESObjectREFR>&);
		Relocation<func_t*> func("", 0x5DB210);
		return func(a_handle, a_refOut);
	}
		
	inline void DebugNotification(const char* a_notification, const char* a_soundToPlay = 0, bool a_cancelIfAlreadyQueued = true)
	{
		using func_t = decltype(&DebugNotification);
		Relocation<func_t> func("", 0xA8B4A0);
		return func(a_notification, a_soundToPlay, a_cancelIfAlreadyQueued);
	}

	inline void	PlaySound(const char* a_editorID)
	{
		using func_t = decltype(&PlaySound);
		Relocation<func_t> func("", 0xA8B8C0);
		return func(a_editorID);
	}

	inline IUIMessageData* CreateUIMessageData(const BSFixedString& a_name)
	{
		using func_t = decltype(&CreateUIMessageData);
		Relocation <func_t> func("", 0x2CF090);
		return func(a_name);
	}
}
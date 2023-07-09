#pragma once

#include "../T/TESForm.h"
#include "../B/BGSEquipSlot.h"

namespace ConsoleRE
{
	class BGSDefaultObjectManager : public TESForm    
	{
	public:
		static constexpr int TypeID = 107;
	public:
		~BGSDefaultObjectManager() override;
		
		// got inlined inside the game, so lets just hope it got init'd by the time this is used.
		static BGSDefaultObjectManager* GetSingleton()
		{
			Relocation<BGSDefaultObjectManager*> Singleton("", 0x20BD860);
			return Singleton.get();
		}

		TESForm* GetObject(uint32_t a_idx) const noexcept
		{
			assert(a_idx < 364);
			return objectInit[a_idx] ? objects[a_idx] : nullptr;
		}

		template <typename T>
		T* GetObject(uint32_t a_idx) const noexcept
		{
			const auto obj = GetObject(a_idx);
			return obj ? obj->As<T>() : nullptr;
		}

		//
		BGSEquipSlot* GetLeftEquipedSlot() const	{ return GetObject<BGSEquipSlot>(19); }
		BGSEquipSlot* GetRightEquippedSlot() const	{ return GetObject<BGSEquipSlot>(20); }
		BGSEquipSlot* GetEquipedSlots() const		{ return GetObject<BGSEquipSlot>(21); }
	public:
		TESForm*		objects[364];
		bool			objectInit[364];
	};
	static_assert(sizeof(BGSDefaultObjectManager) == 0xCF0);
}
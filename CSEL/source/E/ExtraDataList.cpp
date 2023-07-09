#include "ExtraDataList.h"

#include "../B/BGSKeyword.h"
#include "../B/BSExtraData.h"

#include "../E/ExtraAshPileRef.h"
#include "../E/ExtraCount.h"
#include "../E/ExtraEncounterZone.h"
#include "../E/ExtraHealth.h"
#include "../E/ExtraLinkedRef.h"
#include "../E/ExtraMissingLinkedRefIDs.h"
#include "../E/ExtraOwnership.h"
#include "../E/ExtraReferenceHandle.h"
#include "../E/ExtraSoul.h"
#include "../E/ExtraTextDisplayData.h"

#include "../G/GameSettingCollection.h"

#include "../T/TESBoundObject.h"
#include "../T/TESForm.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	bool					BaseExtraList::PresenceBitfield::HasType(uint32_t a_type) const
	{
		uint32_t index = (a_type >> 3);
		if (index >= 0x18)
		{
			return false;
		}

		const uint8_t bitMask = 1 << (a_type % 8);
		return (bits[index] & bitMask) != 0;
	}

	void					BaseExtraList::PresenceBitfield::MarkType(uint32_t a_type, bool a_cleared)
	{
		uint32_t	index = (a_type >> 3);
		uint8_t		bitMask = 1 << (a_type % 8);
		uint8_t&	flag = bits[index];

		if (a_cleared)
		{
			flag &= ~bitMask;
		}
		else
		{
			flag |= bitMask;
		}
	}

	//
	BSExtraData*			ExtraDataList::GetByType(uint32_t a_type)
	{
		return GetByTypeImpl(a_type);
	}

	const BSExtraData*		ExtraDataList::GetByType(uint32_t a_type) const 
	{
		return GetByTypeImpl(a_type);
	}

	bool					ExtraDataList::HasType(uint32_t a_type) const
	{
		BSReadLockGuard locker(m_lock);
		return m_extralist.presence != nullptr && m_extralist.presence->HasType(a_type);
	}

	bool					ExtraDataList::Remove(uint8_t type, BSExtraData* toRemove)
	{
		bool s_removed = false;

		BSWriteLockGuard locker(m_lock);
		if (!toRemove)
			return false;

		if (m_extralist.data == toRemove)
		{
			m_extralist.data = m_extralist.data->next;
			s_removed = true;
		}
		else
		{
			for (auto it = m_extralist.data; it; it = it->next)
			{
				if (it->next == toRemove)
				{
					it->next = toRemove->next;
					s_removed = true;
					break;
				}
			}
		}

		if (s_removed)
			m_extralist.presence->MarkType(type, true);

		return s_removed;
	}
	
	bool					ExtraDataList::Add(uint32_t a_typeID, BSExtraData* a_toadd)
	{
		BSWriteLockGuard locker(m_lock);

		if (!a_toadd || HasType(a_typeID))
		{
			return false;
		}

	
		BSExtraData* next = m_extralist.data;
		m_extralist.data = a_toadd;
		a_toadd->next = next;
		m_extralist.presence->MarkType(a_typeID, false);

		return true;
	}

	uint32_t				ExtraDataList::GetAshPileRef()
	{
		auto xAshRef = GetByType<ExtraAshPileRef>();
		return xAshRef ? xAshRef->ashPileRef : 0;
	}

	int32_t					ExtraDataList::GetCount()
	{
		auto xCount = GetByType<ExtraCount>();
		return xCount ? xCount->count : 1;
	}

	const char*				ExtraDataList::GetDisplayName(TESBoundObject* a_form)
	{
		float       health = 1.0F;

		ExtraHealth* extraHealth = GetByType<ExtraHealth>();
		if (extraHealth)
			health = extraHealth->health;

		ExtraTextDisplayData* extraTextDisplayData = GetExtraTextDisplayData();
		if (!extraTextDisplayData && health != 1.0f)
		{
			extraTextDisplayData = new ExtraTextDisplayData();
			Add(ExtraTextDisplayData::TypeID, extraTextDisplayData);
		}

		if (extraTextDisplayData)
			return extraTextDisplayData->GetDisplayName(a_form, health);
		else
			return nullptr;
	}

	BGSEncounterZone*		ExtraDataList::GetEncounterZone()
	{
		auto xZone = GetByType<ExtraEncounterZone>();
		return xZone ? xZone->zone : nullptr;
	}

	ExtraTextDisplayData*	ExtraDataList::GetExtraTextDisplayData()
	{
		using func_t = decltype(&ExtraDataList::GetExtraTextDisplayData);
		Relocation<func_t> func("", 0x545C0);
		return func(this);
	}

	TESObjectREFR*			ExtraDataList::GetLinkedRef(BGSKeyword* a_keyword)
	{
		BSReadLockGuard locker(m_lock);

		auto xLinkedRef = GetByType<ExtraLinkedRef>();
		if (!xLinkedRef) 
		{
			return nullptr;
		}

		TESObjectREFR* linkedRef = nullptr;
		for (auto& entry : xLinkedRef->linkedRefs) 
		{
			if (entry.keyword == a_keyword) 
			{
				linkedRef = entry.refr;

				if (!linkedRef && HasType(0x06))
				{
					auto xMissingLinkedRefIDs = GetByType<ExtraMissingLinkedRefIDs>();
					linkedRef = xMissingLinkedRefIDs ? xMissingLinkedRefIDs->GetLinkedRef(a_keyword) : nullptr;
				}
			}

			if (linkedRef) 
			{
				break;
			}
		}

		return linkedRef;
	}
	
	TESForm*				ExtraDataList::GetOwner()
	{
		auto xOwner = GetByType<ExtraOwnership>();
		return xOwner ? xOwner->owner : nullptr;
	}

	uint32_t				ExtraDataList::GetSoulLevel()
	{
		auto xSoul = GetByType<ExtraSoul>();
		return xSoul ? xSoul->soul : 0;
	}

	//
	BSExtraData*			ExtraDataList::GetByTypeImpl(uint32_t a_type) const
	{
		BSReadLockGuard locker(m_lock);

		if (!HasType(a_type))
		{
			return nullptr;
		}

		for (auto iter = m_extralist.data; iter; iter = iter->next)
		{
			if (iter->GetType() == a_type)
			{
				return iter;
			}
		}

		return nullptr;
	}

	void					ExtraDataList::MarkType(uint32_t a_type, bool a_cleared)
	{
		return m_extralist.presence->MarkType(a_type, a_cleared);
	}
}
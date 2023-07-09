#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSExtraData.h"

namespace ConsoleRE
{	
	class ExtraTextDisplayData;
	class BGSEncounterZone;
	class TESBoundObject;
	class BGSKeyword;
	class TESObjectREFR;
	class TESForm;

	class BaseExtraList
	{
	public:
		struct PresenceBitfield
		{
		public:
			bool HasType(uint32_t a_type) const;
			void MarkType(uint32_t a_type, bool a_cleared);
		public:
			uint8_t bits[0x18];
		};
	public:
		BSExtraData*            data;
		PresenceBitfield*       presence;
	};
	static_assert(sizeof(BaseExtraList) == 0x10);

	class ExtraDataList
	{
	public:
		BSExtraData*			GetByType(uint32_t a_type);
		const BSExtraData*		GetByType(uint32_t a_type) const;

		bool					HasType(uint32_t a_type) const;
		bool					Remove(uint8_t type, BSExtraData* toRemove);

		template <typename T>
		T*						GetByType() { return static_cast<T*>(GetByType(T::TypeID)); }

		template <typename T>
		bool					HasType() { return HasType(T::TypeID); }

		template <typename T>
		bool					Remove(T* a_toRemove) { return Remove(T::TypeID, a_toRemove); }
		
		//
		bool					Add(uint32_t a_typeID, BSExtraData* a_toadd);
		uint32_t				GetAshPileRef();
		int32_t					GetCount();
		const char*				GetDisplayName(TESBoundObject* a_form);
		BGSEncounterZone*		GetEncounterZone();
		ExtraTextDisplayData*	GetExtraTextDisplayData();
		TESObjectREFR*			GetLinkedRef(BGSKeyword* a_keyword);
		TESForm*				GetOwner();
		uint32_t				GetSoulLevel();
	private:
		BSExtraData*			GetByTypeImpl(uint32_t a_type) const;
		void					MarkType(uint32_t a_type, bool a_cleared);
	public:
		BaseExtraList					m_extralist;	
		mutable BSReadWriteLock			m_lock;
	};
	static_assert(sizeof(ExtraDataList) == 0x20, "");
}
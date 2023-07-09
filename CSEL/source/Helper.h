#pragma once

#include "A/Actor.h"
#include "T/TESForm.h"
#include "E/ExtraHotkey.h"
#include "I/InventoryEntryData.h"
#include "T/TESObjectWEAP.h"
#include "B/BGSBipedObjectForm.h"
#include "T/TESLevItem.h"
#include "T/TESFaction.h"
#include "B/BGSPerk.h"


#include "RTTI.h"

#include <stdint.h>
#include <set>
#include <map>

using namespace ConsoleRE;

namespace Helper
{
	class ExtraContainerInfo
	{
	public:
		ExtraContainerInfo() : m_vector(), m_map()
		{
			m_vector.reserve(128);
		}

		ExtraContainerInfo(BSSimpleList<InventoryEntryData*>* a_inv) : ExtraContainerInfo()
		{
			if (a_inv)
			{
				a_inv->Visit(*this);
			}
		}

		bool Accept(InventoryEntryData* a_data)
		{
			if (a_data)
			{
				m_vector.push_back(a_data);
				m_map[a_data->form] = m_vector.size() - 1;
			}

			return true;
		}

		bool IsVaild(ContainerObject* a_entry, int32_t& a_num)
		{
			if (a_entry)
			{
				a_num = a_entry->count;
				auto* pForm = a_entry->obj;

				auto cast = TES_RTTI(pForm, TESForm, TESLevItem);
				if (cast)
				{
					return false;
				}

				if (auto it = m_map.find(pForm); it != m_map.end())
				{
					uint32_t idx = it->second;
					auto* pXdata = m_vector[idx];
					if (pXdata)
					{
						a_num += pXdata->countDelta;
					}

					m_vector[idx] = nullptr;
				}
				
				if (a_num > 0)
				{
					return true;
				}

				return false;
			}

			return false;
		}

		void ExportForms(BGSListForm* receiver)
		{
			auto it = m_vector.begin();
			auto end = m_vector.end();

			while (it != end)
			{
				InventoryEntryData* extraData = (*it);
				if (extraData && (extraData->countDelta > 0))
				{
					receiver->AddForm(extraData->form);
				}

				++it;
			}
		}

		void ExportForms(std::vector<TESForm*>& receiver)
		{
			auto it = m_vector.begin();
			auto end = m_vector.end();

			while (it != end)
			{
				InventoryEntryData* extraData = (*it);
				if (extraData && (extraData->countDelta > 0)) 
				{
					receiver.push_back(extraData->form);
				}

				++it;
			}
		}

		float ExportFormWeight()
		{
			float weight = 0.0;

			auto it = m_vector.begin();
			auto end = m_vector.end();

			while (it != end)
			{
				InventoryEntryData* extraData = (*it);
				if (extraData && (extraData->countDelta > 0)) 
				{
					auto GetWeight = [](TESForm* a_form) -> float
					{
						if (!a_form)
							return 0.0;

						TESWeightForm* pWeight = TES_RTTI(a_form, TESForm, TESWeightForm);
						if (pWeight)
							return pWeight->weight;

						return 0.0;
					};

					weight += GetWeight(extraData->form) * extraData->countDelta;
				}
				++it;
			}
			return weight;
		}

		InventoryEntryData* ExportForm(uint32_t n, uint32_t count) 
		{
			auto end = m_vector.end();
			auto it = m_vector.begin();
			
			while (it != end)
			{
				InventoryEntryData* extraData = (*it);
				if (extraData && (extraData->countDelta > 0)) 
				{
					if (count == n)
					{
						return extraData;
					}
					count++;
				}
				++it;
			}
			return NULL;
		}

		uint32_t ExportFormCount() 
		{
			uint32_t count	= 0;
			auto end		= m_vector.end();
			auto it			= m_vector.begin();
			
			while (it != end) 
			{
				InventoryEntryData* extraData = (*it);
				if (extraData && (extraData->countDelta > 0)) 
				{
					count++;
				}

				++it;
			}
			return count;
		}

	public:
	std::vector<InventoryEntryData*> m_vector;
	std::map<TESForm*, uint32_t>	 m_map;
	};
	
	class ExtraContainerMerger
	{
	public:
		enum UnionType : int64_t
		{
			kNone			= 0 << 0,
			kBGSListForm	= 1 << 1,
			kVMArray		= 1 << 2,
		};

		union SharedData
		{
		public:
			SharedData(BGSListForm* a_listForm) : m_ListForm(a_listForm)
			{
			}

			SharedData(std::vector<TESForm*>* a_VMRetArray) : m_VMRetArray(a_VMRetArray) 
			{
			}
		public:
			std::vector<TESForm*>*	m_VMRetArray;
			BGSListForm*			m_ListForm;
		};
	public:
		ExtraContainerMerger(ExtraContainerInfo& a_extracontainer, BGSListForm* a_list) : m_extraContainerInfo(a_extracontainer), m_UnionType(UnionType::kBGSListForm), m_sharedData(a_list)
		{
		}

		ExtraContainerMerger(ExtraContainerInfo& a_extracontainer, std::vector<TESForm*>* a_VMRetArray) : m_extraContainerInfo(a_extracontainer), m_UnionType(UnionType::kVMArray), m_sharedData(a_VMRetArray)
		{
		}

		bool Accept(ContainerObject* a_data)
		{
			int32_t s_numbObj = 0;
			if (m_extraContainerInfo.IsVaild(a_data, s_numbObj))
			{
				switch (m_UnionType)
				{
					case UnionType::kNone:
						break;
					case UnionType::kBGSListForm:
						m_sharedData.m_ListForm->AddForm(a_data->obj);
						break;
					case UnionType::kVMArray:
						m_sharedData.m_VMRetArray->push_back(a_data->obj);
						break;
				}
			}

			return true;
		}

	public:
		ExtraContainerInfo& m_extraContainerInfo;
		int64_t				m_UnionType;
		SharedData			m_sharedData;
	};

	class ExtraContainerWeightInfo
	{
	public:
		ExtraContainerWeightInfo(ExtraContainerInfo& a_info) : m_extraContainerInfo(a_info)
		{
		}

		bool Accept(ContainerObject* a_obj)
		{
			int32_t numObjects = 0;
			if (m_extraContainerInfo.IsVaild(a_obj, numObjects))
			{
				auto GetWeight = [](TESForm* a_form) -> float
				{
					if (!a_form)
						return 0.0;

					TESWeightForm* pWeight = TES_RTTI(a_form, TESForm, TESWeightForm);
					if (pWeight)
						return pWeight->weight;

					return 0.0;
				};

				m_weight += GetWeight(a_obj->obj) * numObjects;
			}

			return true;
		}
	public:
		ExtraContainerInfo& m_extraContainerInfo;
		float				m_weight{ 0.0f };
	};

	class ExtraContainerInfoFinder
	{
	public:
		ExtraContainerInfoFinder(ExtraContainerInfo& a_info, uint32_t a_Idx) :  m_info(a_info), m_Foundidx(a_Idx)
		{
		}

		bool Accept(ContainerObject* a_obj)
		{
			int32_t numObjects = 0;
			if (m_info.IsVaild(a_obj, numObjects))
			{
				if (m_Curidx == m_Foundidx)
				{
					return true;
				}
				
				m_Curidx++;
			}
			return false;
		}
	public:
		ExtraContainerInfo& m_info;
		uint32_t			m_Curidx{ 0 };
		uint32_t			m_Foundidx{ 0 };
	};

	class ExtraContainerCountVaild
	{
	public:
		ExtraContainerCountVaild(ExtraContainerInfo& a_info) : m_info(a_info)
		{ 
		}
		
		bool Accept(ContainerObject* a_obj)
		{
			int32_t numObjects = 0;
			return m_info.IsVaild(a_obj, numObjects);
		}
	public:
		ExtraContainerInfo& m_info;

	};

	class ExtraContainerItemCouter
	{
	public:
		ExtraContainerItemCouter(TESForm* a_form) : m_count(0), m_item(a_form)
		{
		}
		
		bool Accept(ContainerObject* a_obj)
		{
			if (a_obj->obj == m_item)
				m_count += a_obj->count;
			
			return true;
		}
	public:
		uint32_t m_count;
		TESForm* m_item;
	};
	
	//
	template <class Op>
	class EquipmentSlotMatcherT
	{
	public:
		EquipmentSlotMatcherT(Op& a_formMatcher, bool a_IsWorn = true, bool a_IsWornLeft = true) : 
			m_foundForm(0), m_FoundList(0), m_formmatcher(a_formMatcher), m_IsWorn(a_IsWorn), m_IsWornLeft(a_IsWornLeft)
		{

		}

		bool Accept(InventoryEntryData* a_EntryData)
		{
			if (a_EntryData)
			{
				auto s_ExtendList = a_EntryData->extraLists;
				if (s_ExtendList && m_formmatcher.Matches(a_EntryData->form))
				{
					for (BSSimpleList<ExtraDataList*>::Iterator it = s_ExtendList->Head(); it; ++it)
					{
						auto pExtraDataList = it.get()->m_item;
						if (pExtraDataList)
						{
							if ((m_IsWorn && pExtraDataList->HasType(0x16)) || (m_IsWornLeft && pExtraDataList->HasType(0x17)))
							{
								m_foundForm = a_EntryData->form;
								m_FoundList = pExtraDataList;
								return false;
							}
						}
					}
				}
			}

			return true;
		}

		void Get(TESBoundObject*& a_dstForm, ExtraDataList*& a_dstdist)
		{
			a_dstForm = m_foundForm;
			a_dstdist = m_FoundList;
		}
	public:
		// [Out]
		TESBoundObject*	  m_foundForm{ 0 };
		ExtraDataList*	  m_FoundList{ 0 };
		
		// [temp]
		Op&		m_formmatcher;
		bool	m_IsWorn;
		bool	m_IsWornLeft;
	};

	class HotkeyFinder
	{
	public:
		HotkeyFinder(uint8_t a_hotkey) : m_matchHotkey(a_hotkey), m_matchForm(0), m_foundForm(0), m_foundHotkey(0)
		{}

		HotkeyFinder(TESForm* a_hotkeyForm) : m_matchHotkey(-1), m_matchForm(a_hotkeyForm), m_foundForm(0), m_foundHotkey(0)
		{}

		bool Accept(InventoryEntryData* a_entry)
		{
			int32_t n = 0;

			if (!a_entry)
				return true;

			if (m_matchForm && m_foundForm != a_entry->form)
				return true;

			auto* ExtendList = a_entry->extraLists;
			if (!ExtendList)
				return true;

			
			auto* ExtraDataList = ExtendList->GetItem(n);
			while (ExtraDataList)
			{
				if (ExtraHotkey* extraHotkey = ExtraDataList->GetByType<ExtraHotkey>())
				{
					if (m_matchForm)
					{
						m_foundForm = a_entry->form;
						m_foundHotkey = extraHotkey;
						return false;
					}
					else
					{
						if (extraHotkey->hotkey == m_matchHotkey)
						{
							m_foundForm = a_entry->form;
							m_foundHotkey = extraHotkey;
							return false;
						}
					}
				}

				n++;
				ExtraDataList = ExtendList->GetItem(n);
			}

			return true;
		}

		void Get(TESForm*& a_dstForm, ExtraHotkey*& a_dstHotkey)
		{
			a_dstForm = m_foundForm;
			a_dstHotkey = m_foundHotkey;
		}
	public:
		uint32_t				m_matchHotkey;
		TESForm*				m_matchForm{ 0 };

		// temp storage, 
		TESForm*				m_foundForm{ 0 };
		ExtraHotkey*			m_foundHotkey{ 0 };

	};
	
	class MatchEquipmentSlot
	{
	public:
		MatchEquipmentSlot(Actor* a_actor, uint32_t a_hand, uint32_t a_slot) : m_actor(a_actor), m_mask(a_slot), m_hand(a_hand) { }

		bool Matches(TESForm* pForm)
		{
			if (pForm)
			{
				if (pForm->FormType != TESObjectWEAP::TypeID)
				{
					BGSBipedObjectForm* pBip = TES_RTTI(pForm, TESForm, BGSBipedObjectForm);
					if (pBip)
						return (pBip->GetSlotMask() & m_mask) != 0;

				}
				else if (m_mask == 0)
				{
					TESForm * equippedForm = m_actor->GetEquippedObject(m_hand == 0);
					return (equippedForm && equippedForm == pForm);
				}
			}
			return false;
		}
	public:
		Actor*				m_actor;
		uint32_t			m_mask;
		uint32_t			m_hand;
	};

	class EquipmentFormMatcher
	{
	public:
		EquipmentFormMatcher(TESForm* a_form) : m_form(a_form) { }
	public:
		bool Matches(TESForm* a_form)
		{
			return a_form == m_form;
		}
	public:
		TESForm* m_form{ nullptr };
	};

	class EquipmentSlotMatcher
	{
	public:
		EquipmentSlotMatcher(uint32_t a_slot) : m_slot(a_slot) { }
	public:
		bool Matches(TESForm* a_form)
		{
			if (a_form)
			{
				auto* bipOpject = TES_RTTI(a_form, TESForm, BGSBipedObjectForm);
				if (bipOpject)
				{
					return (bipOpject->GetSlotMask() & m_slot) != 0;
				}
			}

			return false;
		}
	public:
		uint32_t m_slot;
	};

}
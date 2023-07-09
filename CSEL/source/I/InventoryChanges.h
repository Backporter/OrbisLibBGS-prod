#pragma once

#include "../B/BSTList.h"
#include "../F/FormTypes.h"
#include "../I/InventoryEntryData.h"

#include <stdint.h>

namespace ConsoleRE
{
	class ExtraDataList;
	class InventoryEntryData;

	class InventoryChanges
	{
	public:
		class IItemChangeVisitor
		{
		public:
			virtual ~IItemChangeVisitor();

			virtual bool Visit(InventoryEntryData* a_entryData) = 0;
			virtual bool Unk_03();
			virtual bool Unk_04(InventoryEntryData* a_entryData, void*, bool& a_visited);
		public:
		};
		static_assert(sizeof(IItemChangeVisitor) == 0x8);

		class FindBestSoulGemVisitor : public IItemChangeVisitor
		{
		public:
			~FindBestSoulGemVisitor() override = default;
			
			// override (IItemChangeVisitor)
			bool Visit(InventoryEntryData* a_entryData) override;
		public:
			Actor*		m_target;
			TESSoulGem*	m_bestSoulGem;
		};
		static_assert(sizeof(FindBestSoulGemVisitor) == 0x18);
	public:
		InventoryChanges();
		explicit InventoryChanges(TESObjectREFR* a_ref);
		~InventoryChanges();
	public:
		BSSimpleList<InventoryEntryData*>* entryList { nullptr };
		TESObjectREFR*					   owner { nullptr };
		float							   totalWeight { 0.0f };
		float							   armorWeight { 0.0f };
		bool                               changed { false };
		uint8_t							   unk19 { 0 };
		uint8_t							   unk1A { 0 };
		uint8_t							   unk1B { 0 };
		uint32_t						   unk1C { 0 };
	private:
		void Ctor(TESObjectREFR* a_ref);
		void Dtor();
	};
	static_assert(sizeof(InventoryChanges) == 0x20);
}
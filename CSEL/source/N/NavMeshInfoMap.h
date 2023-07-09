#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSNavmeshInfoMap.h"
#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"
#include "../P/PrecomputedNavmeshInfoPathMap.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct NavMeshInfo;

	class NavMeshInfoMap :
		public TESForm,
		public BSNavmeshInfoMap,
		public PrecomputedNavmeshInfoPathMap
	{
	public:
		static constexpr int TypeID = 59;

		~NavMeshInfoMap() override;

		// override (TESForm)
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		void SetAltered(bool a_set) override;

		// override (BSNavmeshInfoMap)
		BSNavmeshInfo* GetNavMeshInfoFixID(uint32_t a_id) override;
		BSNavmeshInfo* GetNavmeshInfo(uint32_t a_id) override;
		void           GetAllNavMeshInfo(BSTArray<BSNavmeshInfo*>& a_results) override;
		void           BuildListOfConnectedInfos(const BSNavmeshInfo* a_info, BSTArray<BSNavmeshInfo*>& a_results) override;
		void           ForEach(IVisitor* a_visitor) override;
	public:
		bool                                                 updateAll;
		uint8_t												 pad79;
		uint16_t											 pad7A;
		BSTHashMap<uint32_t, NavMeshInfo*>					 infoMap;
		BSTHashMap<uint64_t, BSTArray<BSNavmeshInfo*>*>		 ckNavMeshInfoMap;
		mutable BSReadWriteLock                              mapLock;
		bool                                                 init;
		uint8_t												 padE9;
		uint16_t											 padEA;
	};
	static_assert(sizeof(NavMeshInfoMap) == 0xB8);
}
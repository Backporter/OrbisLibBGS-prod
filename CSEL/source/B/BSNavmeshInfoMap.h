#pragma once

#include "../B/BSTEvent.h"

namespace ConsoleRE
{
	struct BSNavmeshInfo;

	class BSNavmeshInfoMap
	{
	public:
		struct IVisitor
		{
		public:
			virtual ~IVisitor();

			// add
			virtual BSContainer::ForEachResult Visit(const BSNavmeshInfo* a_info) = 0;
		};
		static_assert(sizeof(IVisitor) == 0x8);

		virtual ~BSNavmeshInfoMap();

		// add
		virtual BSNavmeshInfo* GetNavMeshInfoFixID(uint32_t a_id) = 0;
		virtual BSNavmeshInfo* GetNavmeshInfo(uint32_t a_id) = 0;
		virtual void           GetAllNavMeshInfo(BSTArray<BSNavmeshInfo*>& a_results) = 0;
		virtual void           BuildListOfConnectedInfos(const BSNavmeshInfo* a_info, BSTArray<BSNavmeshInfo*>& a_results) = 0;
		virtual void           ForEach(IVisitor* a_visitor) = 0;
	};
	static_assert(sizeof(BSNavmeshInfoMap) == 0x8);
}
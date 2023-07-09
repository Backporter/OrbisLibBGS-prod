#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTSmartPointer.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BSAnimationGraphChannel;
	class BSAnimationGraphManager;
	class BShkbAnimationGraph;
	class NiAVObject;
	class NiPoint3;

	class IAnimationGraphManagerHolder
	{
	public:
		virtual	~IAnimationGraphManagerHolder();
		
		// add
		virtual bool	 NotifyAnimationGraph(const BSFixedString& a_eventname);
		virtual bool	 GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>&) const = 0;
		virtual bool	 SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>&) = 0;
		virtual bool	 PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodes);
		virtual bool     ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>&) = 0;
		virtual uint32_t Unk_07();
		virtual uint32_t Unk_08();
		virtual bool	 SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph);
		virtual uint32_t Unk_10();
		virtual bool	 CreateAnimationChannels(BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>& animGraphChannels);
		virtual void	 PostCreateAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr);
		virtual uint32_t Unk_13();
		virtual void	 PostChangeAnimationManager(const BSTSmartPointer<BShkbAnimationGraph>& a_arg1, const BSTSmartPointer<BShkbAnimationGraph>& a_arg2);
		virtual uint32_t Unk_15();
		virtual uint32_t GetGraphVariableCacheSize() const;
		virtual bool	 GetGraphVariableImpl3(const BSFixedString& VariableName, bool& a_out) const;
		virtual bool	 GetGraphVariableImpl2(const BSFixedString& VariableName, int32_t& a_out) const;
		virtual bool	 GetGraphVariableImpl1(const BSFixedString& VariableName, float& a_out) const;

		bool GetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_out);
		bool GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out);
		bool GetGraphVariableInt(const BSFixedString& a_variableName, int32_t& a_out);
		bool GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out);
		bool GetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_out);
		bool SetAnimationGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_in);
		bool SetGraphVariableBool(const BSFixedString& a_variableName, bool a_in);
		bool SetGraphVariableInt(const BSFixedString& a_variableName, int32_t a_in);
		bool SetGraphVariableFloat(const BSFixedString& a_variableName, float a_in);
		bool SetGraphVariableNiPoint3(const BSFixedString& a_variableName, NiPoint3& a_in);
	};
	static_assert(sizeof(IAnimationGraphManagerHolder) == 0x8);
}
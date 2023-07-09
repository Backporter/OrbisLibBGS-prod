#pragma once
#include "../B/BSTEvent.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSAnimationGraphEvent.h"
#include "../B/BSAnimationGraphChannel.h"
#include "../B/BShkbAnimationGraph.h"

namespace ConsoleRE
{
	class BShkbAnimationGraph;
	struct BSAnimationGraphEvent;

	union hkbVariableValue
	{
		bool         b;
		int32_t		 i;
		float        f;
	};
	static_assert(sizeof(hkbVariableValue) == 0x4, "hkbVariableValue");

	struct AnimVariableCacheInfo
	{
	public:
		BSFixedString     variableName;  // 00
		hkbVariableValue* variable;      // 08
	};
	static_assert(sizeof(AnimVariableCacheInfo) == 0x10, "AnimVariableCacheInfo");

	struct BSAnimationGraphVariableCache
	{
	public:
		// members
		BSTArray<AnimVariableCacheInfo> variableCache; 
		void*                           unk18;         
		void*                           unk20;         
	};
	static_assert(sizeof(BSAnimationGraphVariableCache) == 0x20, "BSAnimationGraphVariableCache");

	class BSAnimationGraphManager: public BSTEventSink<BSAnimationGraphEvent>, public BSIntrusiveRefCounted
	{
	public:
		BSAnimationGraphManager();
		virtual ~BSAnimationGraphManager();
	public:
		// override (BSTEventSink<BSAnimationGraphEvent>)
		virtual BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent*, BSTEventSource<BSAnimationGraphEvent>*) override;
	public:
		uint32_t											pad0C;
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  boundChannels;         
		BSTArray<BSTSmartPointer<BSAnimationGraphChannel>>  bumpedChannels;        
		BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>> graphs;                
		BSTArray<BSTSmartPointer<BSAnimationGraphManager>>  subManagers;           
		BSAnimationGraphVariableCache                       variableCache; // 58
		mutable BSSpinLock                                  updateLock;            
		mutable BSSpinLock                                  dependentManagerLock;  
		uint32_t											activeGraph;           
		uint32_t											generateDepth;         
	};
	// static_assert(sizeof(BSAnimationGraphManager) == 0xA0, "BSAnimationGraphManager");
}
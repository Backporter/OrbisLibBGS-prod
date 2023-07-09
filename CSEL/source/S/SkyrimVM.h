#pragma once

#include "../B/BSAtomic.h"
#include "../B/BSTEvent.h"
#include "../B/BSTFreeList.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTMessageQueue.h"
#include "../B/BSTSmartPointer.h"
#include "../C/CompiledScriptLoader.h"
#include "../D/DelayFunctor.h"
#include "../F/FragmentSystem.h"
#include "../H/HandlePolicy.h"
#include "../I/IFreezeQuery.h"
#include "../I/IStackCallbackSaveInterface.h"
#include "../L/Logger.h"
#include "../P/Profiler.h"
#include "../S/SavePatcher.h"
#include "../S/SimpleAllocMemoryPagePolicy.h"
#include "../S/SkyrimScriptObjectBindPolicy.h"
#include "../S/SkyrimScriptStore.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class IVirtualMachine;
		class IVMDebugInterface;
		class IVMSaveLoadInterface;
		struct StatsEvent;

		namespace Internal
		{
			class VirtualMachine;
		}
	}

	struct PositionPlayerEvent;
	struct TESActivateEvent;
	struct TESActiveEffectApplyRemoveEvent;
	struct TESActorLocationChangeEvent;
	struct TESBookReadEvent;
	struct TESCellAttachDetachEvent;
	struct TESCellFullyLoadedEvent;
	struct TESCombatEvent;
	struct TESContainerChangedEvent;
	struct TESDeathEvent;
	struct TESDestructionStageChangedEvent;
	struct TESEnterBleedoutEvent;
	struct TESEquipEvent;
	struct TESFastTravelEndEvent;
	struct TESFormDeleteEvent;
	class TESFurnitureEvent;
	struct TESGrabReleaseEvent;
	struct TESHitEvent;
	struct TESInitScriptEvent;
	struct TESLoadGameEvent;
	struct TESLockChangedEvent;
	struct TESMagicEffectApplyEvent;
	struct TESMagicWardHitEvent;
	struct TESMoveAttachDetachEvent;
	struct TESObjectLoadedEvent;
	struct TESObjectREFRTranslationEvent;
	struct TESOpenCloseEvent;
	struct TESPackageEvent;
	struct TESPerkEntryRunEvent;
	struct TESPlayerBowShotEvent;
	struct TESQuestInitEvent;
	struct TESQuestStageEvent;
	struct TESResetEvent;
	struct TESResolveNPCTemplatesEvent;
	struct TESSceneActionEvent;
	struct TESSceneEvent;
	struct TESScenePhaseEvent;
	struct TESSellEvent;
	struct TESSleepStartEvent;
	struct TESSleepStopEvent;
	struct TESSpellCastEvent;
	struct TESSwitchRaceCompleteEvent;
	struct TESTopicInfoEvent;
	struct TESTrackedStatsEvent;
	struct TESTrapHitEvent;
	struct TESTriggerEnterEvent;
	struct TESTriggerEvent;
	struct TESTriggerLeaveEvent;
	struct TESUniqueIDChangeEvent;

	class SkyrimVM :
		public BSScript::IFreezeQuery,                       
		public BSScript::IStackCallbackSaveInterface,        
		public BSTEventSink<TESActivateEvent>,               
		public BSTEventSink<TESActiveEffectApplyRemoveEvent>,
		public BSTEventSink<TESActorLocationChangeEvent>,    
		public BSTEventSink<TESBookReadEvent>,               
		public BSTEventSink<TESCellAttachDetachEvent>,       
		public BSTEventSink<TESCellFullyLoadedEvent>,        
		public BSTEventSink<TESCombatEvent>,                 
		public BSTEventSink<TESContainerChangedEvent>,       
		public BSTEventSink<TESDeathEvent>,                  
		public BSTEventSink<TESDestructionStageChangedEvent>,
		public BSTEventSink<TESEnterBleedoutEvent>,          
		public BSTEventSink<TESEquipEvent>,                  
		public BSTEventSink<TESFormDeleteEvent>,             
		public BSTEventSink<TESFurnitureEvent>,              
		public BSTEventSink<TESGrabReleaseEvent>,            
		public BSTEventSink<TESHitEvent>,                    
		public BSTEventSink<TESInitScriptEvent>,             
		public BSTEventSink<TESLoadGameEvent>,               
		public BSTEventSink<TESLockChangedEvent>,            
		public BSTEventSink<TESMagicEffectApplyEvent>,       
		public BSTEventSink<TESMagicWardHitEvent>,           
		public BSTEventSink<TESMoveAttachDetachEvent>,       
		public BSTEventSink<TESObjectLoadedEvent>,           
		public BSTEventSink<TESObjectREFRTranslationEvent>,  
		public BSTEventSink<TESOpenCloseEvent>,              
		public BSTEventSink<TESPackageEvent>,                
		public BSTEventSink<TESPerkEntryRunEvent>,           
		public BSTEventSink<TESQuestInitEvent>,              
		public BSTEventSink<TESQuestStageEvent>,             
		public BSTEventSink<TESResetEvent>,                  
		public BSTEventSink<TESResolveNPCTemplatesEvent>,    
		public BSTEventSink<TESSceneEvent>,                  
		public BSTEventSink<TESSceneActionEvent>,            
		public BSTEventSink<TESScenePhaseEvent>,             
		public BSTEventSink<TESSellEvent>,                   
		public BSTEventSink<TESSleepStartEvent>,             
		public BSTEventSink<TESSleepStopEvent>,              
		public BSTEventSink<TESSpellCastEvent>,              
		public BSTEventSink<TESTopicInfoEvent>,              
		public BSTEventSink<TESTrackedStatsEvent>,           
		public BSTEventSink<TESTrapHitEvent>,                
		public BSTEventSink<TESTriggerEvent>,                
		public BSTEventSink<TESTriggerEnterEvent>,           
		public BSTEventSink<TESTriggerLeaveEvent>,           
		public BSTEventSink<TESUniqueIDChangeEvent>,         
		public BSTEventSink<TESSwitchRaceCompleteEvent>,     
		public BSTEventSink<TESPlayerBowShotEvent>,          
		public BSTEventSink<TESFastTravelEndEvent>,          
		public BSTEventSink<PositionPlayerEvent>,            
		public BSTEventSink<BSScript::StatsEvent>,           
		public BSTEventSource<BSScript::StatsEvent>          
	{
	public:
		class UpdateDataEvent : public BSIntrusiveRefCounted
		{
		public:
			void release()
			{
				if (!DecRef())
				{
					delete this;
				}
			}
		public:
			bool		m_runOnce;		// 0x4
			uint32_t	m_schedTime;	// 0x8
			uint32_t	m_interval;		// 0xC
			uint64_t	m_handle;		// 0x10
		};
		static_assert(sizeof(UpdateDataEvent) == 0x18);

		struct LOSDataEvent : public BSIntrusiveRefCounted
		{
		public:
			uint32_t		m_pad04;
			uint64_t		m_handle;
			uint32_t		m_viewerFormID;
			uint32_t		m_targetFormID;
			uint32_t		m_losEventType;
			uint32_t		m_lastLOSCheckResult;
		};
		static_assert(sizeof(LOSDataEvent) == 0x20);

		struct InventoryEventFilterLists : public BSIntrusiveRefCounted
		{
			BSTHashMap<UnkValue, UnkKey> itemsForFiltering;
			BSTHashMap<UnkValue, UnkKey> itemListsForFiltering;
		};
		static_assert(sizeof(InventoryEventFilterLists) == 0x48);

		struct WaitCall
		{
		public:
			uint32_t					timeToSendEvent;
			uint32_t					stackID;
			BSScript::IVirtualMachine*	vm;
		};
		static_assert(sizeof(WaitCall) == 0x10);
	public:
		~SkyrimVM() override;
	public:
		static SkyrimVM* GetSingleton() 
		{ 
			Relocation<SkyrimVM**> Singleton("SkyrimVM::Singleton", 0x20C5530); 
			return *Singleton; 
		}

		// TBA; [queuedOnUpdateEventLock, queuedOnUpdateEvents, queuedOnUpdateGameEvents]
		uint32_t ClearInvalidRegistrations();
	public:
		BSTSmartPointer<BSScript::IVirtualMachine>																impl;
		BSScript::IVMSaveLoadInterface*																			saveLoadInterface;
		BSScript::IVMDebugInterface*																			debugInterface;
		BSScript::SimpleAllocMemoryPagePolicy																	memoryPagePolicy;
		BSScript::CompiledScriptLoader																			scriptLoader;
		SkyrimScript::Logger																					logger;
		SkyrimScript::HandlePolicy																				handlePolicy;
		SkyrimScript::ObjectBindPolicy																			objectBindPolicy;
		BSTSmartPointer<SkyrimScript::Store>																	scriptStore;
		SkyrimScript::FragmentSystem																			fragmentSystem;
		SkyrimScript::Profiler																					profiler;
		SkyrimScript::SavePatcher																				savePatcher;
		mutable BSSpinLock																						frozenLock;
		uint32_t																								isFrozen;
		mutable BSSpinLock																						currentVMTimeLock;
		uint32_t																								currentVMTime;
		uint32_t																								currentVMMenuModeTime;
		uint32_t																								currentVMGameTime;
		uint32_t																								currentVMDaysPassed;
		mutable BSSpinLock																						queuedWaitEventLock;
		BSTArray<WaitCall>																						queuedWaitCalls;
		BSTArray<WaitCall>																						queuedWaitMenuModeCalls;
		BSTArray<WaitCall>																						queuedWaitGameCalls;
		mutable BSSpinLock																						queuedLOSEventCheckLock;
		BSTArray<BSTSmartPointer<LOSDataEvent>>																	queuedLOSEventChecks;
		uint32_t																								currentLOSEventCheckIndex;
		mutable BSSpinLock																						queuedOnUpdateEventLock;
		BSTArray<BSTSmartPointer<UpdateDataEvent>>																queuedOnUpdateEvents;
		BSTArray<BSTSmartPointer<UpdateDataEvent>>																queuedOnUpdateGameEvents;
		uint32_t																								unk0750;
		mutable BSSpinLock																						registeredSleepEventsLock;
		BSTHashMap<UnkValue, UnkKey>																			registeredSleepEvents;
		mutable BSSpinLock																						registeredStatsEventsLock;
		BSTHashMap<UnkValue, UnkKey>																			registeredStatsEvents;
		BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>										renderSafeFunctorPool1;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>									renderSafeFunctorQueue1;
		BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>										renderSafeFunctorPool2;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>									renderSafeFunctorQueue2;
		BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>										postRenderFunctorPool1;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>									postRenderFunctorQueue1;
		BSTStaticFreeList<BSTSmartPointer<SkyrimScript::DelayFunctor>, 512>										postRenderFunctorPool2;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>									postRenderFunctorQueue2;
		mutable BSSpinLock																						renderSafeQueueLock;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>*									renderSafeQueueToReadFrom;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>*									renderSafeQueueToWriteTo;
		mutable BSSpinLock																						postRenderQueueLock;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>*									postRenderQueueToReadFrom;
		BSTCommonLLMessageQueue<BSTSmartPointer<SkyrimScript::DelayFunctor>>*									postRenderQueueToWriteTo;
		mutable BSSpinLock																						userLogMapLock;
		BSTHashMap<SkyrimScript::Logger*, const char*>															userLogMap;
		mutable BSSpinLock																						currentVMOverstressTimeLock;
		uint32_t																								currentVMOverstressTime;
		uint32_t																								lastVMStackDumpTime;
		mutable BSSpinLock																						InventoryEventFilterMapLock;
		BSTHashMap<InventoryEventFilterLists, uint64_t>															InventoryEventFilterMap;
	};
	static_assert(offsetof(SkyrimVM, impl)					== 0x1E8, "IVirtualMachine");
	static_assert(offsetof(SkyrimVM, saveLoadInterface)		== 0x1F0, "IVMSaveLoadInterface");
	static_assert(offsetof(SkyrimVM, debugInterface)		== 0x1F8, "IVMDebugInterface");
	static_assert(offsetof(SkyrimVM, memoryPagePolicy)		== 0x200, "SimpleAllocMemoryPagePolicy");
	static_assert(offsetof(SkyrimVM, scriptLoader)			== 0x230, "CompiledScriptLoader");
	static_assert(offsetof(SkyrimVM, logger)				== 0x278, "Logger");
	static_assert(offsetof(SkyrimVM, handlePolicy)			== 0x310, "HandlePolicy");
	static_assert(offsetof(SkyrimVM, objectBindPolicy)		== 0x368, "ObjectBindPolicy");
	static_assert(offsetof(SkyrimVM, profiler)				== 0x510, "Profiler");
	static_assert(offsetof(SkyrimVM, savePatcher)			== 0x5C8, "SavePatcher");
}
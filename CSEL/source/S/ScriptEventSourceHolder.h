#pragma once

#include "../B/BSTEvent.h"

namespace ConsoleRE
{
	class TESObjectREFR;
	struct BGSEventProcessedEvent;
	struct TESActivateEvent;
	struct TESActiveEffectApplyRemoveEvent;
	struct TESActorLocationChangeEvent;
	struct TESBookReadEvent;
	struct TESCellAttachDetachEvent;
	struct TESCellFullyLoadedEvent;
	struct TESCellReadyToApplyDecalsEvent;
	struct TESCombatEvent;
	struct TESContainerChangedEvent;
	struct TESDeathEvent;
	struct TESDestructionStageChangedEvent;
	struct TESEnterBleedoutEvent;
	struct TESEquipEvent;
	struct TESFastTravelEndEvent;
	struct TESFormDeleteEvent;
	struct TESFurnitureEvent;
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
	struct TESQuestStageItemDoneEvent;
	struct TESQuestStartStopEvent;
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
	struct TESWaitStartEvent;
	struct TESWaitStopEvent;

	class ScriptEventSourceHolder :
		public BSTEventSource<BGSEventProcessedEvent>,           
		public BSTEventSource<TESActivateEvent>,                 
		public BSTEventSource<TESActiveEffectApplyRemoveEvent>,  
		public BSTEventSource<TESActorLocationChangeEvent>,      
		public BSTEventSource<TESBookReadEvent>,                 
		public BSTEventSource<TESCellAttachDetachEvent>,         
		public BSTEventSource<TESCellFullyLoadedEvent>,          
		public BSTEventSource<TESCellReadyToApplyDecalsEvent>,   
		public BSTEventSource<TESCombatEvent>,                   
		public BSTEventSource<TESContainerChangedEvent>,         
		public BSTEventSource<TESDeathEvent>,                    
		public BSTEventSource<TESDestructionStageChangedEvent>,  
		public BSTEventSource<TESEnterBleedoutEvent>,            
		public BSTEventSource<TESEquipEvent>,                    
		public BSTEventSource<TESFormDeleteEvent>,               
		public BSTEventSource<TESFurnitureEvent>,                
		public BSTEventSource<TESGrabReleaseEvent>,              
		public BSTEventSource<TESHitEvent>,                      
		public BSTEventSource<TESInitScriptEvent>,               
		public BSTEventSource<TESLoadGameEvent>,                 
		public BSTEventSource<TESLockChangedEvent>,              
		public BSTEventSource<TESMagicEffectApplyEvent>,         
		public BSTEventSource<TESMagicWardHitEvent>,             
		public BSTEventSource<TESMoveAttachDetachEvent>,         
		public BSTEventSource<TESObjectLoadedEvent>,             
		public BSTEventSource<TESObjectREFRTranslationEvent>,    
		public BSTEventSource<TESOpenCloseEvent>,                
		public BSTEventSource<TESPackageEvent>,                  
		public BSTEventSource<TESPerkEntryRunEvent>,             
		public BSTEventSource<TESQuestInitEvent>,                
		public BSTEventSource<TESQuestStageEvent>,               
		public BSTEventSource<TESQuestStageItemDoneEvent>,       
		public BSTEventSource<TESQuestStartStopEvent>,           
		public BSTEventSource<TESResetEvent>,                    
		public BSTEventSource<TESResolveNPCTemplatesEvent>,      
		public BSTEventSource<TESSceneEvent>,                    
		public BSTEventSource<TESSceneActionEvent>,              
		public BSTEventSource<TESScenePhaseEvent>,               
		public BSTEventSource<TESSellEvent>,                     
		public BSTEventSource<TESSleepStartEvent>,               
		public BSTEventSource<TESSleepStopEvent>,                
		public BSTEventSource<TESSpellCastEvent>,                
		public BSTEventSource<TESPlayerBowShotEvent>,            
		public BSTEventSource<TESTopicInfoEvent>,                
		public BSTEventSource<TESTrackedStatsEvent>,             
		public BSTEventSource<TESTrapHitEvent>,                  
		public BSTEventSource<TESTriggerEvent>,                  
		public BSTEventSource<TESTriggerEnterEvent>,             
		public BSTEventSource<TESTriggerLeaveEvent>,             
		public BSTEventSource<TESUniqueIDChangeEvent>,           
		public BSTEventSource<TESWaitStartEvent>,                
		public BSTEventSource<TESWaitStopEvent>,                 
		public BSTEventSource<TESSwitchRaceCompleteEvent>,       
		public BSTEventSource<TESFastTravelEndEvent>             
	{
	public:
		static ScriptEventSourceHolder* GetSingleton()
		{
			Relocation<ScriptEventSourceHolder**> Singleton("", 0x20C4318);
			return *Singleton;
		}

		template <class T>
		BSTEventSource<T>* GetEventSource()
		{
			return static_cast<BSTEventSource<T>*>(this);
		}

		template <class T>
		void AddEventSink(BSTEventSink<T>* a_sink)
		{
			GetEventSource<T>()->AddEventSink(a_sink);
		}

		template <class T>
		void RemoveEventSink(BSTEventSink<T>* a_sink)
		{
			GetEventSource<T>()->RemoveEventSink(a_sink);
		}

		template <class T>
		void SendEvent(const T* a_event)
		{
			GetEventSource<T>()->SendEvent(a_event);
		}
	};
	// static_assert(sizeof(ScriptEventSourceHolder) == 0x1290, "#");
}
#pragma once

// #include "../A/AttachedScript.h"
#include "../B/BSAtomic.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTFreeList.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTMessageQueue.h"
#include "../B/BSTSmartPointer.h"
#include "../F/FunctionMessage.h"
#include "../I/IVMDebugInterface.h"
#include "../I/IVMObjectBindInterface.h"
#include "../I/IVMSaveLoadInterface.h"
#include "../I/IVirtualMachine.h"
#include "../L/LinkerProcessor.h"
#include "../S/SuspendedStack.h"


namespace ConsoleRE
{
	class Array;
	class ErrorLogger;
	class IFreezeQuery;
	class IProfilePolicy;
	class ISavePatcherInterface;
	class IStackCallbackFunctor;
	class IStackCallbackSaveInterface;
	class ObjectBindPolicy;
	class Stack;
	struct IMemoryPagePolicy;
	struct IObjectHandlePolicy;
	struct StatsEvent;

	namespace BSScript
	{
		namespace Internal
		{
			class CodeTasklet;

			// 0x9488 on ORBIS, 0x94C0 on NX
			class VirtualMachine : public IVirtualMachine, public IVMObjectBindInterface, public IVMSaveLoadInterface, public IVMDebugInterface, public BSTEventSource<StatsEvent>		
			{
			public:
				struct QueuedUnbindRefs
				{
				public:
					BSTSmartPointer<Object> obj;
					uint32_t				refCount;
					uint32_t				pad0C;
				};
			public:
				~VirtualMachine() override;
				
				// override (IVirtualMachine)
				void                       SetCompiledScriptLoader(CompiledScriptLoader* a_callback) override;
				void					   WriteMessageToLog(char*, Severity) override;
				void                       TraceStack(const char* a_str, uint32_t a_stackID, Severity a_severity = Severity::Info) override;
				void                       Update(float a_budget) override;
				void                       UpdateTasklets(float a_budget) override;
				void                       SetOverstressed(bool a_set) override;
				bool                       IsCompletelyFrozen() override;
				bool                       RegisterObjectType(uint32_t a_typeID, const char* a_className) override;
				bool                       GetScriptObjectType1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) override;
				bool                       GetScriptObjectType2(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) override;
				bool                       GetScriptObjectTypeNoLoad1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) override;
				bool                       GetScriptObjectTypeNoLoad2(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) override;
				bool                       GetTypeIDForScriptObject(const BSFixedString& a_className, uint32_t& a_typeID) override;
				void                       GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_results) override;
				bool                       GetParentNativeType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) override;
				bool                       TypeIsValid(const BSFixedString& a_className) override;
				bool                       ReloadType(const char* a_className) override;
				void                       TasksToJobs(void* a_jobList) override;
				void                       CalculateFullReloadList(void) override;
				bool                       CreateObject1(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr) override;
				bool                       CreateObject2(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) override;
				bool                       CreateArray1(const TypeInfo& a_typeInfo, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) override;
				bool                       CreateArray2(TypeInfo::RawType a_typeID, const BSFixedString& a_className, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) override;
				bool                       BindNativeMethod(IFunction* a_fn) override;
				void                       SetCallableFromTasklets1(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable) override; 
				void                       SetCallableFromTasklets2(const char* a_className, const char* a_fnName, bool a_callable) override;
				void                       ForEachBoundObject(uint64_t a_handle, IForEachScriptObjectFunctor* a_functor) override;
				bool                       FindBoundObject(uint64_t a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) override;
				void                       MoveBoundObjects(uint64_t a_from, uint64_t a_to) override;
				void                       ResetAllBoundObjects(uint64_t a_handle) override;
				bool                       CastObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<ObjectTypeInfo>& a_toTypeInfoPtr, BSTSmartPointer<Object>& a_toObjPtr) override;
				bool                       SetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal) override;
				bool                       GetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal) override;
				bool                       GetVariableValue1(const BSTSmartPointer<Object>& a_objPtr, uint32_t a_index, Variable& a_out) override;
				bool                       GetVariableValue2(uint64_t a_handle, const BSFixedString& a_className, int32_t a_variableIndex, Variable& a_out) override;
				void                       SendEvent(uint64_t a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args) override;
				void                       SendEventAll(const BSFixedString& a_eventName, IFunctionArguments* a_args) override;
				bool                       DispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;
				bool                       DispatchMethodCall1(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;
				bool                       DispatchMethodCall2(uint64_t a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;
				bool                       DispatchUnboundMethodCall(void) override;
				bool                       IsWaitingOnLatent(uint32_t a_stackID) override;
				
				void                       ReturnFromLatent(uint32_t a_stackID, const Variable& a_val) override;
				ErrorLogger*               GetErrorLogger() override;
				IObjectHandlePolicy*       GetObjectHandlePolicy1() override;
				const IObjectHandlePolicy* GetObjectHandlePolicy2() const override;
				ObjectBindPolicy*          GetObjectBindPolicy1() override;
				const ObjectBindPolicy*    GetObjectBindPolicy2() const override;
				ISavePatcherInterface*     GetSavePatcherInterface() override;
				void                       RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink) override;
				void                       UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink) override;
				void                       RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) override;
				void                       UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) override;

				// override (IVMObjectBindInterface)
				uint64_t GetBoundHandle(const BSTSmartPointer<Object>& a_objPtr) const override;
				bool     TypeCanBeBound(const BSFixedString& a_className, uint64_t a_handle) override;
				void     BindObject(BSTSmartPointer<Object>& a_objPtr, uint64_t a_handle, bool a_conditional) override;
				void     HandleLoadedBinding(BSTSmartPointer<Object>& a_objPtr, uint64_t a_handle, bool a_conditional) override;
				void     RemoveAllBoundObjects(uint64_t a_handle) override;
				void     RemoveAllDiskLoadedBoundObjects(uint64_t a_handle) override;
				void     HandleCObjectDeletion(uint64_t a_handle) override;
				void     UnbindObject(const BSTSmartPointer<Object>& a_objPtr) override;
				bool     CreateObjectWithProperties(const BSFixedString& a_className, uint32_t a_numProperties, BSTSmartPointer<Object>& a_objPtr) override;
				bool     InitObjectProperties(BSTSmartPointer<Object>& a_objPtr, void* a_property, bool a_arg3) override;
			public:
				static VirtualMachine* GetSingleton();
				// {
				// 	auto vm = SkyrimVM::GetSingleton();
				// 	return vm ? static_cast<VirtualMachine*>(vm->impl.get()) : nullptr;
				// }


				void RegisterFunction(IFunction* fn);
				// {
				// 	// Atomic count of the number of papyrus functions binded.
				// 	static volatile int g_fncount = 0;
				// 
				// 	// store names
				// 	const char* className = fn->GetObjectTypeName().c_str();
				// 	const char* funcName = fn->GetName().c_str();
				// 
				// 	// Log the Class::Name of the function count
				// 	xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "VirtualMachine::RegisterFunction is registering %s::%s of %u", className, funcName, g_fncount);
				// 
				// 	if (BindNativeMethod(fn))
				// 	{
				// 		// inc
				// 		__sync_add_and_fetch(&g_fncount, 1);
				// 	}
				// 	else
				// 	{
				// 		xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning, "Failed to bind %s::%s[%u]", className, funcName, g_fncount);
				// 	}
				// }
			public:
				ErrorLogger*												errorLogger;
				IMemoryPagePolicy*											memoryPagePolicy;
				IObjectHandlePolicy*										handlePolicy;
				ObjectBindPolicy*											objectBindPolicy;
				IFreezeQuery*												freezeQuery;
				IStackCallbackSaveInterface*								stackCallbackSaveInterface;
				IProfilePolicy*												profilePolicy;
				ISavePatcherInterface*										savePatcherInterface;
				mutable BSSpinLock											typeInfoLock;
				LinkerProcessor												linker;
				BSTHashMap<BSTSmartPointer<ObjectTypeInfo>, BSFixedString>  objectTypeMap;
				BSTHashMap<BSFixedString, uint32_t>                         typeIDToObjectType;
				BSTHashMap<uint32_t, BSFixedString>                         objectTypeToTypeID;
				BSTArray<BSTSmartPointer<ObjectTypeInfo>>                   typesToUnload;
				mutable BSSpinLock                                          funcQueueLock;
				BSTStaticFreeList<FunctionMessage, 1024u>				    funcMsgPool;
				BSTCommonLLMessageQueue<FunctionMessage>				    funcMsgQueue;
				BSTArray<FunctionMessage>                                   overflowFuncMsgs;
				BSTArray<CodeTasklet*>                                      vmTasks;
				uint32_t												    uiWaitingFunctionMessages;
				bool                                                        overstressed;
				bool                                                        initialized;
				uint16_t													pad821E;
				BSTCommonStaticMessageQueue<SuspendedStack, 128u>		    suspendQueue1;
				BSTCommonStaticMessageQueue<SuspendedStack, 128u>		    suspendQueue2;
				BSTArray<SuspendedStack>                                    overflowSuspendArray1;
				BSTArray<SuspendedStack>                                    overflowSuspendArray2;
				mutable BSSpinLock                                          suspendQueueLock;
				BSTCommonStaticMessageQueue<SuspendedStack, 128>*           stacksToResume;
				BSTArray<SuspendedStack>*                                   stacksToResumeOverflow;
				BSTCommonStaticMessageQueue<SuspendedStack, 128>*           stacksToSuspend;
				BSTArray<SuspendedStack>*                                   stacksToSuspendOverflow;
				mutable BSSpinLock                                          runningStacksLock;
				BSTHashMap<uint32_t, BSTSmartPointer<Stack>>                allRunningStacks;
				BSTHashMap<uint32_t, BSTSmartPointer<Stack>>                waitingLatentReturns;
				uint32_t                                                    nextStackID;
				mutable BSSpinLock                                          frozenStacksLock;
				BSScript::Stack*                                            frozenStacks;
				uint32_t													frozenStacksCount;
				uint32_t													freezeState;
				mutable BSSpinLock                                          attachedScriptsLock;
				BSTHashMap<uint64_t, void*>									attachedScripts;
				uint32_t													unk93D8;
				uint32_t													unk93DC;   
				BSTArray<BSTSmartPointer<Object>>                           objectsAwaitingCleanup;
				mutable BSSpinLock                                          arraysLock; 
				uint32_t													nextArrayToClean;
				uint32_t													pad9404;
				BSTArray<BSTSmartPointer<Array>>                            arrays;
				mutable BSSpinLock                                          objectResetLock;
				BSTArray<BSTSmartPointer<Object>>                           objectsAwaitingReset;
				mutable BSSpinLock                                          objectLock;
				BSTHashMap<uint64_t, BSTSmartPointer<Object>>               objectTable;
				BSTHashMap<uint64_t, BSTSmartPointer<Array>>                arrayTable;
				mutable BSSpinLock                                          queuedUnbindLock;
				BSTArray<QueuedUnbindRefs>                                  queuedUnbinds;
				int8_t														saveGameVersion;
				uint32_t													unk94CC;
				uint32_t													unk94D0; 
				WritableStringTable                                         writableStringTable;
				ReadableStringTable                                         readableStringTable;
				BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* writeableTypeTable;
				BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* readableTypeTable;
			};
			static_assert(offsetof(VirtualMachine, linker) == 0xC0);
			static_assert(offsetof(VirtualMachine, funcMsgPool) == 0x1B8);
			static_assert(offsetof(VirtualMachine, funcMsgQueue) == 0x81D0);
			static_assert(offsetof(VirtualMachine, suspendQueue1) == 0x8220);
			static_assert(offsetof(VirtualMachine, suspendQueue2) == 0x8A38);
			static_assert(offsetof(VirtualMachine, frozenStacks) == 0x9308);	
		}
	}
}
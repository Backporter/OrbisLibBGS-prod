#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTEvent.h"
#include "../B/BSTSmartPointer.h"
#include "../E/ErrorLogger.h"
#include "../T/TypeInfo.h"

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		class CompiledScriptLoader;
		class Array;
		class ErrorLogger;
		class IForEachScriptObjectFunctor;
		class IFunction;
		class IFunctionArguments;
		class ISavePatcherInterface;
		class IStackCallbackFunctor;
		class Object;
		class ObjectBindPolicy;
		class ObjectTypeInfo;
		class Variable;

		struct IObjectHandlePolicy;
		struct LogEvent;
		struct StatsEvent;

		class IVirtualMachine : public BSIntrusiveRefCounted
		{
		public:
			using Severity = BSScript::ErrorLogger::Severity;
		public:
			virtual ~IVirtualMachine();

			// add (IVirtualMachine)
			virtual void SetCompiledScriptLoader(CompiledScriptLoader*) = 0;
			virtual void WriteMessageToLog(char*, Severity) = 0;
			virtual void TraceStack(const char* a_str, uint32_t a_stackID, Severity a_severity = Severity::Info) = 0;
			virtual void Update(float a_budget) = 0;
			virtual void UpdateTasklets(float a_budget) = 0;
			virtual void SetOverstressed(bool a_set) = 0;
			virtual bool IsCompletelyFrozen() = 0;
			virtual bool RegisterObjectType(uint32_t a_typeID, const char* a_className) = 0;
			virtual bool GetScriptObjectType2(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfo) = 0;
			virtual bool GetScriptObjectType1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfo) = 0;
			virtual bool GetScriptObjectTypeNoLoad2(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) = 0;
			virtual bool GetScriptObjectTypeNoLoad1(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) = 0;
			virtual bool GetTypeIDForScriptObject(const BSFixedString& a_className, uint32_t& a_typeID) = 0;
			virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_classes) = 0;
			virtual bool GetParentNativeType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) = 0;
			virtual bool TypeIsValid(const BSFixedString& a_className) = 0;
			virtual bool ReloadType(const char* a_className) = 0;
			virtual void TasksToJobs(void* a_jobList) = 0;
			virtual void CalculateFullReloadList(void) = 0;
			virtual bool CreateObject2(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) = 0;
			virtual bool CreateObject1(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr) = 0;
			virtual bool CreateArray2(TypeInfo::RawType a_typeID, const BSFixedString& a_className, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) = 0;
			virtual bool CreateArray1(const TypeInfo& a_typeInfo, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) = 0;
			virtual bool BindNativeMethod(IFunction* a_fn) = 0;
			virtual void SetCallableFromTasklets2(const char* a_className, const char* a_fnName, bool a_callable) = 0;
			virtual void SetCallableFromTasklets1(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable) = 0;
			virtual void ForEachBoundObject(uint64_t a_handle, IForEachScriptObjectFunctor* a_functor) = 0;
			virtual bool FindBoundObject(uint64_t a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) = 0;
			virtual void MoveBoundObjects(uint64_t a_from, uint64_t a_to) = 0;
			virtual void ResetAllBoundObjects(uint64_t a_handle) = 0;
			virtual bool CastObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<ObjectTypeInfo>& a_toTypeInfoPtr, BSTSmartPointer<Object>& a_toObjPtr) = 0;
			virtual bool SetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal) = 0;
			virtual bool GetPropertyValue(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal) = 0;
			virtual bool GetVariableValue2(uint64_t a_handle, const BSFixedString& a_className, int32_t a_variableIndex, Variable& a_out) = 0;
			virtual bool GetVariableValue1(const BSTSmartPointer<Object>& a_objPtr, uint32_t a_index, Variable& a_out) = 0;
			virtual void SendEvent(uint64_t a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args) = 0;
			virtual void SendEventAll(const BSFixedString& a_eventName, IFunctionArguments* a_args) = 0;
			virtual bool DispatchStaticCall(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) = 0;
			virtual bool DispatchMethodCall2(uint64_t a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) = 0;
			virtual bool DispatchMethodCall1(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) = 0;
			virtual bool DispatchUnboundMethodCall(void) = 0;
			virtual bool IsWaitingOnLatent(uint32_t a_stackID) = 0;
			virtual void ReturnFromLatent(uint32_t a_stackID, const Variable& a_val) = 0;
			virtual ErrorLogger* GetErrorLogger() = 0;
			virtual IObjectHandlePolicy* GetObjectHandlePolicy1() = 0;
			virtual const IObjectHandlePolicy* GetObjectHandlePolicy2() const = 0;
			virtual ObjectBindPolicy* GetObjectBindPolicy1() = 0;
			virtual const ObjectBindPolicy* GetObjectBindPolicy2() const = 0;
			virtual ISavePatcherInterface* GetSavePatcherInterface() = 0;
			virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;
			virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;
			virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;
			virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;
		public:
			bool                       CreateArray(const TypeInfo& a_typeInfo, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) { return CreateArray1(a_typeInfo, a_size, a_arrayPtr); }
			bool                       CreateArray(TypeInfo::RawType a_typeID, const BSFixedString& a_className, uint32_t a_size, BSTSmartPointer<Array>& a_arrayPtr) { return CreateArray2(a_typeID, a_className, a_size, a_arrayPtr); }
			bool                       CreateObject(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr) { return CreateObject1(a_className, a_property, a_objPtr); }
			bool                       CreateObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) { return CreateObject2(a_className, a_result); }
			bool                       DispatchMethodCall(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) { return DispatchMethodCall1(a_obj, a_fnName, a_args, a_result); }
			bool                       DispatchMethodCall(uint64_t a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) { return DispatchMethodCall2(a_handle, a_className, a_fnName, a_args, a_result); }
			ObjectBindPolicy*          GetObjectBindPolicy() { return GetObjectBindPolicy1(); }
			const ObjectBindPolicy*    GetObjectBindPolicy() const { return GetObjectBindPolicy2(); }
			IObjectHandlePolicy*       GetObjectHandlePolicy() { return GetObjectHandlePolicy1(); }
			const IObjectHandlePolicy* GetObjectHandlePolicy() const { return GetObjectHandlePolicy2(); }
			bool                       GetScriptObjectType(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) { return GetScriptObjectType1(a_className, a_outTypeInfoPtr); }
			bool                       GetScriptObjectType(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) { return GetScriptObjectType2(a_typeID, a_outTypeInfoPtr); }
			bool                       GetScriptObjectTypeNoLoad(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_typeInfoPtr) { return GetScriptObjectTypeNoLoad1(a_className, a_typeInfoPtr); }
			bool                       GetScriptObjectTypeNoLoad(uint32_t a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outTypeInfoPtr) { return GetScriptObjectTypeNoLoad2(a_typeID, a_outTypeInfoPtr); }
			bool                       GetVariableValue(const BSTSmartPointer<Object>& a_objPtr, uint32_t a_index, Variable& a_out) { return GetVariableValue1(a_objPtr, a_index, a_out); }
			bool                       GetVariableValue(uint64_t a_handle, const BSFixedString& a_className, int32_t a_variableIndex, Variable& a_out) { return GetVariableValue2(a_handle, a_className, a_variableIndex, a_out); }
			void					   SetCallableFromTasklets(const char* a_className, const char* a_stateName, const char* a_fnName, bool a_callable) { return SetCallableFromTasklets1(a_className, a_stateName, a_fnName, a_callable); }
			void					   SetCallableFromTasklets(const char* a_className, const char* a_fnName, bool a_callable) { return SetCallableFromTasklets2(a_className, a_fnName, a_callable); }
		private:
			uint32_t pad0C;
		};
		static_assert(sizeof(IVirtualMachine) == 0x10);
	}
}
#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSAtomic.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	template <class T>
	class BSTEventSink;

	enum class BSEventNotifyControl
	{
		kContinue = 0,
		kStop = 1
	};

	struct BSContainer
	{
		enum class ForEachResult
		{
			kContinue = 0,
			kStop = 1
		};
	};

	template <class T>
	class BSTEventSource
	{
	public:
		using Sink = BSTEventSink<T>;
	public:
		BSTEventSource() : sinks(), pendingRegisters(), pendingUnregisters(), lock(), notifying(false), pad51(0), pad52(0) {}

		void AddEventSink(Sink* a_eventSink)
		{
			using func_t = decltype(&BSTEventSource<T>::AddEventSink);
			Relocation<func_t> func("", 0x658280);
			return func(this, a_eventSink);
		}
		
		void RemoveEventSink(Sink* a_eventSink)
		{
			using func_t = decltype(&BSTEventSource<T>::RemoveEventSink);
			Relocation<func_t> func("",0x4D4430);
			return func(this, a_eventSink);
		}
		
		void SendEventSink(const T* a_event)
		{
			using func_t = decltype(&BSTEventSource<T>::SendEventSink);
			Relocation<func_t> func("", 0xC2B40);
			return func(this, a_event);
		}
	public:
		BSTArray<Sink*>			sinks;
		BSTArray<Sink*>			pendingRegisters;
		BSTArray<Sink*>			pendingUnregisters;
		mutable BSSpinLock		lock;
		bool					notifying;
		uint8_t					pad51;
		uint16_t				pad52;
	};
	static_assert(sizeof(BSTEventSource<void*>) == 0x48);

	template <class T>
	class BSTEventSink
	{
	public:
		virtual ~BSTEventSink() = default;

		// add
		virtual BSEventNotifyControl ProcessEvent(const T*, BSTEventSource<T>*) = 0;
	};
	static_assert(sizeof(BSTEventSink<void>) == 0x8);
}
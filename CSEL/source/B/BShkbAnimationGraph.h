#pragma once
#include "../B/BSIRagdollDriver.h"
#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTEvent.h"
#include "../B/BSAnimationGraphEvent.h"

namespace ConsoleRE
{
	class BSTransformDeltaEvent;

	class BShkbAnimationGraph : public BSIRagdollDriver, public BSIntrusiveRefCounted, public BSTEventSource<BSTransformDeltaEvent>, public BSTEventSource<BSAnimationGraphEvent>
	{
	public:
		virtual ~BShkbAnimationGraph();

		template <typename T>
		BSTEventSource<T>* GetEventSource()
		{
			return static_cast<BSTEventSource<T>*>(this);
		}

		template <typename T>
		void AddEventSource(BSTEventSink<T>* a_eventsource)
		{
			GetEventSource<T>()->AddEventSink(a_eventsource);
		}

		template <typename T>
		void RemoveEventSource(BSTEventSink<T>* a_eventsource)
		{
			GetEventSource<T>()->RemoveEventSink(a_eventsource);
		}

		bool GetGraphVariableBool(const BSFixedString& a_variableName, bool& a_out)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, bool&);
			Relocation<func_t*> func("", 0xBA5F50);
			return func(this, a_variableName, a_out);
		}

		bool GetGraphVariableFloat(const BSFixedString& a_variableName, float& a_out)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, float&);
			Relocation<func_t*> func("", 0xBA6030);
			return func(this, a_variableName, a_out);
		}

		bool GetGraphVariableInt(const BSFixedString& a_variableName, int& a_out)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, int&);
			Relocation<func_t*> func("", 0xBA6110);
			return func(this, a_variableName, a_out);
		}

		bool SetGraphVariableFloat(const BSFixedString& a_variableName, const float a_in)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, const float);
			Relocation<func_t*> func("", 0xD71670);
			return func(this, a_variableName, a_in);
		}

		/*
		bool SetGraphVariableBool(const BSFixedString& a_variableName, const bool a_in)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, const bool);
			REL::Relocation<func_t> func{ RELOCATION_ID(63609, 62708) };
			return func(this, a_variableName, a_in);
		}

		bool SetGraphVariableInt(const BSFixedString& a_variableName, const int a_in)
		{
			using func_t = bool(BShkbAnimationGraph* const, const BSFixedString&, const int);
			REL::Relocation<func_t> func{ RELOCATION_ID(63607, 62710) };
			return func(this, a_variableName, a_in);
		}
		*/
	public:
	};
}
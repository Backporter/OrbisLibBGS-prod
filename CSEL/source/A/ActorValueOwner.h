#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class ActorValueOwner
	{
	public:
		virtual ~ActorValueOwner();

		// add
		virtual float GetActorValue(uint32_t a_akValue);
		virtual float GetPermanentActorValue(uint32_t a_akValue);
		virtual float GetBaseActorValue(uint32_t a_akValue);
		virtual void  SetBaseActorValue(uint32_t a_akValue, float a_value);
		virtual void  ModActorValue(uint32_t a_akValue, float a_value);
		virtual void  RestoreActorValue(uint32_t a_modifier, uint32_t a_akValue, float a_value);
		virtual void  SetActorValue(uint32_t a_akValue, float a_value);
		virtual bool  GetIsPlayerOwner() const;
	public:
	};
	static_assert(sizeof(ActorValueOwner) == 0x8);

}
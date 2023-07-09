#pragma once

#include "../H/hkReferencedObject.h"

namespace ConsoleRE
{
	class hkpCharacterContext : public hkReferencedObject
	{
	public:
		virtual ~hkpCharacterContext();
	public:
		uint32_t									   characterType;
		void*										   stateManager;
		uint32_t									   currentState;
		uint32_t									   previousState;
		bool                                           filterEnable;
		uint8_t										   pad29;
		uint16_t									   pad2A;
		float                                          maxLinearAcceleration;
		float                                          maxLinearVelocity;
		float                                          gain;
	};
	static_assert(sizeof(hkpCharacterContext) == 0x30);
}
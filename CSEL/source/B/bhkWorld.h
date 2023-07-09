#pragma once

#include "../B/BSAtomic.h"
#include "../B/bhkSerializable.h"

//
#include "../B/BSTArray.h"
#include "../H/hkVector4.h"

namespace ConsoleRE
{
	struct bhkPickData;
	class BGSAcousticSpaceListener;
	class hkpSuspendInactiveAgentsUtil;
	class NiAVObject;
	class bhkConstraintProjector;

	// 0xC5F0
	class bhkWorld : public bhkSerializable
	{
	public:
		~bhkWorld() override;

		// override (bhkSerializable)
		const NiRTTI* GetRTTI() const override;
	public:
		uint8_t							unk0020[0x320];
		uint8_t							unk0340[0x6400];
		uint8_t							unk6740[0x5DC0];
		BSTArray<void*>					unkC500;
		BSTArray<void*>					unkC518;
		BSTArray<void*>					unkC530;
		BSTArray<void*>					unkC548;
		uint64_t						unkC560;
		uint32_t						unkC568;
		float							unkC56C;
		bhkConstraintProjector*			constraintProjector;
		uint64_t						unkC578;
		uint32_t						unkC580;
		float							unkC584;
		uint64_t						unkC588;
		uint64_t						unkC590;
		mutable BSReadWriteLock			worldLock;
		mutable BSReadWriteLock			unkC5A0;
		uint64_t						unkC5A8;
		hkVector4						unkC5B0;
		uint64_t						unkC5C0;
		BGSAcousticSpaceListener*		acousticSpaceListener;
		hkpSuspendInactiveAgentsUtil*	suspendInactiveAgentsUtil;
		uint32_t						unkC5D8;
		uint32_t						unkC5DC;
		uint32_t						unkC5E0;
		uint32_t						unkC5E4;
		uint32_t						unkC5E8;
		uint32_t						unkC5EC;
		float							tau;
		float							damping;
		uint8_t							unkC5F8;
		bool							toggleCollision;
		uint16_t						unkC5FA;
		uint16_t						unkC5FC;
		uint16_t						unkC5FE;
	};
	static_assert(sizeof(bhkWorld) == 0xC5F0);
}
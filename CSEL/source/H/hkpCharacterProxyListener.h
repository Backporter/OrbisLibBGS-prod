#pragma once

#include "../H/hkArray.h"
#include "../H/hkVector4.h"
#include "../M/MemoryManager.h"

namespace ConsoleRE
{
	class hkContactPoint;
	class hkpCharacterProxy;
	class hkpRigidBody;
	struct hkpRootCdPoint;
	struct hkpSimplexSolverInput;

	struct hkpCharacterObjectInteractionEvent
	{
	public:
		hkVector4     position;
		hkVector4     normal;
		float         objectImpulse;
		float         timestep;
		float         projectedVelocity;
		float         objectMassInv;
		hkpRigidBody* body;
		uint64_t	  pad38;
	};
	static_assert(sizeof(hkpCharacterObjectInteractionEvent) == 0x40);

	struct hkpCharacterObjectInteractionResult
	{
	public:
		hkVector4 objectImpulse;
		hkVector4 impulsePosition;
	};
	static_assert(sizeof(hkpCharacterObjectInteractionResult) == 0x20);

	class hkpCharacterProxyListener
	{
	public:
		virtual ~hkpCharacterProxyListener();

		// add
		virtual void ProcessConstraintsCallback(const hkpCharacterProxy* a_proxy, const hkArray<hkpRootCdPoint>& a_manifold, hkpSimplexSolverInput& a_input);
		virtual void ContactPointAddedCallback(const hkpCharacterProxy* a_proxy, const hkpRootCdPoint& a_point);
		virtual void ContactPointRemovedCallback(const hkpCharacterProxy* a_proxy, const hkpRootCdPoint& a_point);
		virtual void CharacterInteractionCallback(hkpCharacterProxy* a_proxy, hkpCharacterProxy* a_otherProxy, const hkContactPoint& a_contact);
		virtual void ObjectInteractionCallback(hkpCharacterProxy* a_proxy, const hkpCharacterObjectInteractionEvent& a_input, hkpCharacterObjectInteractionResult& a_output);
	};
	static_assert(sizeof(hkpCharacterProxyListener) == 0x8);

}
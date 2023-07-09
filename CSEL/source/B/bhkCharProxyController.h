#pragma once

#include "../B/bhkCharacterController.h"
#include "../B/bhkCharacterProxy.h"
#include "../H/hkpCharacterProxyListener.h"

namespace ConsoleRE
{
	class hkpCharacterProxy;

	class bhkCharProxyController : public hkpCharacterProxyListener, public bhkCharacterController
	{
	public:
		~bhkCharProxyController() override;

		// override (hkpCharacterProxyListener)
		void ProcessConstraintsCallback(const hkpCharacterProxy* a_proxy, const hkArray<hkpRootCdPoint>& a_manifold, hkpSimplexSolverInput& a_input) override;
		void ContactPointAddedCallback(const hkpCharacterProxy* a_proxy, const hkpRootCdPoint& a_point) override;
		void ContactPointRemovedCallback(const hkpCharacterProxy* a_proxy, const hkpRootCdPoint& a_point) override;
		void CharacterInteractionCallback(hkpCharacterProxy* a_proxy, hkpCharacterProxy* a_otherProxy, const hkContactPoint& a_contact) override;
		void ObjectInteractionCallback(hkpCharacterProxy* a_proxy, const hkpCharacterObjectInteractionEvent& a_input, hkpCharacterObjectInteractionResult& a_output) override;

		// override (bhkCharacterController)
		void GetLinearVelocityImpl(hkVector4& a_velocity) const override;
		void SetLinearVelocityImpl(const hkVector4& a_velocity) override;
	public:
		bhkCharacterProxy proxy;	
		void*             unk5A0;
		uint64_t		  unk5A8;
	};
	static_assert(sizeof(bhkCharProxyController) == 0x580);
}
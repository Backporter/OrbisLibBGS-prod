#pragma once

#include "../H/hkArray.h"
#include "../H/hkReferencedObject.h"
#include "../H/hkVector4.h"
#include "../H/hkpEntityListener.h"
#include "../H/hkpPhantomListener.h"

namespace ConsoleRE
{
	class hkpAllCdPointCollector;
	class hkpCharacterProxyListener;
	class hkpPhantom;
	class hkpRigidBody;
	class hkpShapePhantom;
	class hkpTriggerVolume;
	struct hkpRootCdPoint;
	struct hkpSurfaceConstraintInfo;

	class hkpCharacterProxy : public hkReferencedObject, public hkpEntityListener, public hkpPhantomListener
	{
	public:
		~hkpCharacterProxy() override;

		// override (hkReferencedObject)
		void CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;

		// override (hkpEntityListener)
		void EntityRemovedCallback(hkpEntity* a_entity) override;

		// override (hkpPhantomListener)
		void PhantomRemovedCallback(hkpPhantom* a_phantom) override;

		// add
		virtual void UpdateManifold(const hkpAllCdPointCollector& a_startPointCollector, const hkpAllCdPointCollector& a_castCollector, hkArray<hkpRootCdPoint>& a_manifold, hkArray<hkpRigidBody*>& a_bodies, hkArray<hkpPhantom*>& a_phantoms, bool a_isMultithreaded = false);
		virtual void ExtractSurfaceConstraintInfo(const hkpRootCdPoint& a_hit, hkpSurfaceConstraintInfo& a_surfaceOut, float a_timeTravelled) const;
	public:
	};
}
#pragma once

#include "../H/hkArray.h"
#include "../H/hkMultiThreadCheck.h"
#include "../H/hkReferencedObject.h"
#include "../H/hkStepInfo.h"
#include "../H/hkpSolverInfo.h"
#include "../H/hkpWorldCinfo.h"

namespace ConsoleRE
{
	class hkCriticalSection;
	class hkdWorld;
	class hknpWorld;
	class hkpActionListener;
	class hkpBroadPhase;
	class hkpBroadPhaseBorder;
	class hkpBroadPhaseBorderListener;
	class hkpCollisionDispatcher;
	class hkpCollisionFilter;
	class hkpConstraintListener;
	class hkpContactImpulseLimitBreachedListener;
	class hkpContactListener;
	class hkpConvexListFilter;
	class hkpEntityEntityBroadPhaseListener;
	class hkpEntityListener;
	class hkpIslandActivationListener;
	class hkpIslandPostCollideListener;
	class hkpIslandPostIntegrateListener;
	class hkpPhantom;
	class hkpPhantomBroadPhaseListener;
	class hkpPhantomListener;
	class hkpSimulation;
	class hkpSimulationIsland;
	class hkpTreeWorldManager;
	class hkpTypedBroadPhaseDispatcher;
	class hkpWorldDeletionListener;
	class hkpWorldExtension;
	class hkpWorldMaintenanceMgr;
	class hkpWorldOperationQueue;
	class hkpWorldPostCollideListener;
	class hkpWorldPostIntegrateListener;
	class hkpWorldPostSimulationListener;
	class hkWorldMemoryAvailableWatchDog;
	struct hkpDebugInfoOnPendingOperationQueues;
	struct hkpMtThreadStructure;
	struct hkpProcessCollisionInput;
	struct hkpViolatedConstraintArray;
	struct hkpWorldRayCastInput;
	struct hkpWorldRayCastOutput;

	class hkpWorld : public hkReferencedObject
	{
	public:
		~hkpWorld() override;

		// override (hkReferencedObject)
		void CalcContentStatistics(hkStatisticsCollector* a_collector, const hkClass* a_class) const override;

		inline void CastRay(const hkpWorldRayCastInput& a_input, hkpWorldRayCastOutput& a_output) const
		{
			using func_t = decltype(&hkpWorld::CastRay);
			Relocation<func_t> func("", 0xCC2FC0);
			return func(this, a_input, a_output);
		}
	public:
	};
}
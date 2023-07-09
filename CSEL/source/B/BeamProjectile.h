#pragma once

#include "../P/Projectile.h"
#include "../B/BSTEvent.h"

namespace ConsoleRE
{
	class BSProceduralGeomEvent;
	struct BeamProjectileImpactEvent;

	class BeamProjectile : public Projectile, public BSTEventSource<BeamProjectileImpactEvent>, public BSTEventSink<BSProceduralGeomEvent>
	{
	public:
		static constexpr int TypeID = 66;
		
		~BeamProjectile() override;

		// override (BSTEventSink<BSProceduralGeomEvent>)
		BSEventNotifyControl ProcessEvent(const BSProceduralGeomEvent* a_event, BSTEventSource<BSProceduralGeomEvent>* a_eventSource) override;
	public:
	};
	// static_assert(sizeof(BeamProjectile) == 0x248);
}
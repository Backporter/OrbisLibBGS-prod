#pragma once

#include "../B/BSTArray.h"
// #include "../H/hkRefPtr.h"
#include "../N/NiPoint3.h"
#include "../P/Projectile.h"

	namespace ConsoleRE
{
	class ConeProjectile : public Projectile
	{
	public:
		static constexpr int TypeID = 68;

		~ConeProjectile() override;
	public:
		uint32_t                 impactResult;
		float                    environmentTimer;
		float                    coneAngleTangent;
		float                    initialCollisionSphereRadius;
		NiPoint3                 origin;
		uint32_t				 pad1F4;
		void*					 collisionShape;
		BSTArray<void*>          collisions;
	};
}
#pragma once

#include "../P/Projectile.h"

namespace ConsoleRE
{
	class BarrierProjectile : public Projectile
	{
	public:
		static constexpr int TypeID = 69;

		struct CollisionData
		{
		public:
			uint32_t ref;
			uint32_t count;
		};
		static_assert(sizeof(CollisionData) == 0x8);
	public:
		~BarrierProjectile() override;
	public:
		float                   width;
		uint32_t				pad1DC;
		BSTArray<CollisionData> collisionData;
	};
	// static_assert(sizeof(BarrierProjectile) == 0x200);
}
#pragma once
#include "../P/Projectile.h"

namespace ConsoleRE
{
	class GrenadeProjectile : public Projectile
	{
	public:
		static constexpr int TypeID = 65;

		GrenadeProjectile();
		virtual ~GrenadeProjectile();
	public:
	};
}
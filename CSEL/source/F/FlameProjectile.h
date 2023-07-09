#pragma once

#include "../P/Projectile.h"

namespace ConsoleRE
{
	class FlameProjectile : public Projectile
	{
	public:
		static constexpr int TypeID = 67;
	public:
		~FlameProjectile() override;
	public:
	};
}
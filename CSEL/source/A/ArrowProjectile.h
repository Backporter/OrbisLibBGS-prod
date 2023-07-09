#pragma once

#include "../M/MissileProjectile.h"

namespace ConsoleRE
{
	class ArrowProjectile : public MissileProjectile
	{
	public:
		static constexpr int TypeID = 64;

		virtual ~ArrowProjectile();
	public:
	};
}
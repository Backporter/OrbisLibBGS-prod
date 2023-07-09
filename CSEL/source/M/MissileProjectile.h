#pragma once

#include "../P/Projectile.h"

namespace ConsoleRE
{
	class MissileProjectile : public Projectile
	{
	public:
		static constexpr int TypeID = 63;

		~MissileProjectile() override;
	public:
		uint32_t	  impactResult;
		bool          waitingToInitialize3D;
		uint8_t		  unk1DD;               
		uint16_t	  unk1DE;               
	};
}
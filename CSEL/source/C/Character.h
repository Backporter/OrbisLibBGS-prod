#pragma once

#include "../A/Actor.h"

namespace ConsoleRE
{
	class Character : public Actor
	{
	public:
		static constexpr int TypeID = 62;
	public:
		~Character() override;
		
		// add
		virtual void CharacterUnk_02();
		virtual void CharacterUnk_03();
	public:
	};
	static_assert(sizeof(Character) == 0x2A8);
}
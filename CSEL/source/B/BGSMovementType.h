#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSMovementType : public TESForm
	{
	public:
		static constexpr int TypeID = 127;
	public:
		~BGSMovementType() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		BSFixedString typeName;
		float		  speeds[5][2];
		float		  rotateWhileMovingRun;
		float         directional;
		float         movementSpeed;
		float         rotationSpeed;
	};
	static_assert(sizeof(BGSMovementType) == 0x60);
}
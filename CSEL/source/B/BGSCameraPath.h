#pragma once

#include "../B/BSTList.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSCameraShot;
	class NiFormArray;

	class BGSCameraPath : public TESForm
	{
	public:
		static constexpr int TypeID = 97;

		~BGSCameraPath() override;
	public:
		TESCondition                 conditions;
		BSSimpleList<BGSCameraShot*> shots;
		uint8_t						 flags;
		uint8_t						 pad39;
		uint16_t					 pad3A;
		uint32_t					 pad3C;
		NiFormArray*                 childPaths;
		BGSCameraPath*               parentPath;
		BGSCameraPath*               prevPath;
	};
	static_assert(sizeof(BGSCameraPath) == 0x58);
}
#pragma once

#include "../B/BGSPreloadable.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSProjectile : 
		public TESBoundObject, 
		public TESFullName, 
		public TESModel, 
		public BGSPreloadable, 
		public BGSDestructibleObjectForm
	{
	public:
		static constexpr int TypeID = 50;
		
		~BGSProjectile() override;
	public:
	};
}
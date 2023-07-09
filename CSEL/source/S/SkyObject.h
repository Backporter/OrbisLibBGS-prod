#pragma once

#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class NiNode;
	class Sky;

	class SkyObject
	{
	public:
		virtual ~SkyObject();

		// add
		virtual NiNode* GetRoot();
		virtual void    Unk_03();
		virtual void    Update(Sky* a_sky, float a_arg2);
	public:
		NiPointer<NiNode> root;
	};
	static_assert(sizeof(SkyObject) == 0x10);
}
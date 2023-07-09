#pragma once

#include "../N/NiRefObject.h"

namespace ConsoleRE
{
	class DetectionListener : public NiRefObject
	{
	public:
		~DetectionListener() override;

		// add
		virtual void Unk_03() = 0;
		virtual void Unk_04();
		virtual void Unk_05();
	};
	static_assert(sizeof(DetectionListener) == 0x10);
}
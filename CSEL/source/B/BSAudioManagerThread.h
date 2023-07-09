#pragma once

#include "../B/BSThread.h"

namespace ConsoleRE
{
	// 0x48
	class BSAudioManagerThread : public BSThread
	{
	public:
		~BSAudioManagerThread() override;

		// override (BSThread)
		uint32_t WaitForEx() override;
	public:
	};
}
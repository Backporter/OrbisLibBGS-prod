#pragma once

#include "../B/BSAudio.h"

#include <stdint.h>
#include <stdio.h>

namespace ConsoleRE
{
	class BSOrbisAudio : public BSAudio
	{
	public:
		virtual ~BSOrbisAudio();

		// override(BSAudio)
		void*	 Unk_04() override;
		void	 Unk_05() override;
		void*	 Unk_06() override;

		void	 Unk_07() override;
		void	 Unk_08() override;
		uint32_t Unk_09() override;
		void	 Unk_0A() override;
		void*	 Unk_0B() override;
	private:
	};
	// 0x590
	static_assert(sizeof(BSOrbisAudio) != 0, "class size mismatch");
}
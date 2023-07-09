#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisGameSound
	{
	public:
		virtual ~BSOrbisGameSound();
		class Ngs2DataSrc
		{
		public:
			virtual ~Ngs2DataSrc();
		private:
			uint8_t pad[0x100];
		};
	private:
		uint8_t pad[0x130];
	};
	// 0x130
	static_assert(sizeof(BSOrbisGameSound) != 0, "class size mismatch");
}
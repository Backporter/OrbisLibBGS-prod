#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisAudioOut
	{
	public:
		virtual ~BSOrbisAudioOut();
		virtual void Unk01(void); // sub_E19BC0
		virtual void Unk02(void); // sub_E19C10
		virtual void Unk03(void); // sub_E19D90
		virtual void Unk04(void); // sub_E18EE0
		virtual void Unk05(void); // sub_E18F90
		virtual void Unk06(void); // sub_E18FA0
		virtual void Unk07(void); // sub_E183C0
		virtual void Unk08(void); // sub_E18130
		virtual void Unk09(void); // sub_E187E0
		virtual void Unk10(void); // sub_E18C70
		virtual void Unk11(void); // sub_E18E40

		class AudioOutputThread
		{
		public:
			virtual ~AudioOutputThread();
		};

	private:
		uint8_t pad[0x590];
	};
	// 0x590
	static_assert(sizeof(BSOrbisAudioOut) != 0, "class size mismatch");
}
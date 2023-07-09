#pragma once

#include "../B/BSKeyboardDevice.h"

namespace ConsoleRE
{
	class BSOrbisKeyboardDevice : public BSKeyboardDevice
	{
	public:
		using func_t = void(void*);
	public:
		virtual ~BSOrbisKeyboardDevice();
		
		// override (BSIInputDevice)
		void Initialize() override;
		void Process(float) override;
		void Finalize() override;
		void Reset() override;

		// override (BSKeyboardDevice)
		void Unk_0A() override;
		void Unk_0B() override;
	public:
		uint64_t			   Unk50;
		BSOrbisKeyboardDevice* Unk58;
		func_t*				   Unk60;
		uint64_t			   Unk68;
		float				   UNK70;
		float				   UNK74;
		bool				   UNK78;
		bool				   Unk79;
		uint16_t			   Pad7A;
		uint32_t			   Pad7C;
	};
	static_assert(sizeof(BSOrbisKeyboardDevice) == 0x80, "#");
}
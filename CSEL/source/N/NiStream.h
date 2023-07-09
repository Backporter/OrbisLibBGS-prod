#pragma once

namespace ConsoleRE
{
	class NiObject;

	class NiStream
	{
	public:
		virtual ~NiStream();
		
		// add
		virtual void Unk_01(void);
		virtual void Unk_02(void);
		virtual void Unk_03(void);
		virtual void Unk_04(void);
		virtual void Unk_05(void);
		virtual void Unk_06(void);
		virtual void Unk_07(void);
		virtual void Unk_08(void);
		virtual bool RegisterSaveObject(NiObject* a_object);
		virtual void Unk_0A(void);
		virtual void Unk_0B(void);
		virtual void Unk_0C(void);
		virtual void Unk_0D(void);
		virtual void Unk_0E(void);
		virtual void Unk_0F(void);
		virtual void Unk_10(void);
		virtual void Unk_11(void);
		virtual void Unk_12(void);
		virtual void Unk_13(void);
		virtual void Unk_14(void);
		virtual void Unk_15(void);
		virtual void Unk_16(void);
		virtual void Unk_17(void);
	public:
	};
}
#pragma once
#include "../../../OrbisUtil/include//Relocation.h"
#include "../B/BSTArray.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisSystemUtility
	{
	public:
		BSOrbisSystemUtility();
		virtual ~BSOrbisSystemUtility();

		virtual uint32_t Unk_02(void);
		virtual size_t	 Unk_03(char*, size_t*);
		virtual uint32_t Unk_04(void);
		virtual uint32_t Init(void);
		virtual uint32_t UnInit(void);
		virtual void	 Unk_07();
		virtual bool	 Unk_08();
		virtual void	 Unk_09();
		virtual uint32_t Unk_10(void);
		virtual void	 Unk_11();
		virtual void	 Unk_12();
		virtual void	 Unk_13();
		virtual uint32_t GetSystemString6(char* buf, size_t bufflen);
		virtual void	 Unk_15();
		virtual void	 Unk_16();
		virtual void	 Unk_17();

		static inline BSOrbisSystemUtility* GetSingleton()
		{
			typedef BSOrbisSystemUtility*(*__GetSingleton)();
			static Relocation<__GetSingleton> GetSingleton(0x1684040);
			return GetSingleton();
		}
	private:
	};

	static_assert(sizeof(BSOrbisSystemUtility) != 0, "class size mismatch");
}
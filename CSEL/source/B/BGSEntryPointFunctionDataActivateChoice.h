#pragma once
#include "../B/BGSEntryPointFunctionData.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionDataActivateChoice : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataActivateChoice();
		virtual ~BGSEntryPointFunctionDataActivateChoice();

		virtual uint32_t Unk_02(void*) override;
		virtual bool	 Unk_03(void*) override;
		virtual void	 Unk_04(void*) override;
		virtual void	 Unk_05(void*) override;
		virtual uint32_t Unk_06(void*) override;
		virtual void	 Unk_07(void*) override;
		virtual uint32_t Unk_08(void*) override;
	public:
		BSFixedString                              Unk08;
		BGSPerk*                                   Unk10;
		SpellItem*                                 Unk18;
		uint16_t								   Unk20;
		uint16_t								   Unk22;
		uint32_t								   Unk24;
	};
	static_assert(sizeof(BGSEntryPointFunctionDataActivateChoice) == 0x28, "");
}
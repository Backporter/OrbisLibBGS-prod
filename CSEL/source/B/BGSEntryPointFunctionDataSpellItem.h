#pragma once
#include "../B/BGSEntryPointFunctionData.h"
#include "../S/SpellItem.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionDataSpellItem : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataSpellItem();
		virtual ~BGSEntryPointFunctionDataSpellItem();

		virtual uint32_t Unk_02(void*) override;
		virtual bool	 Unk_03(void*) override;
		virtual void	 Unk_04(void*) override;
		virtual void	 Unk_05(void*) override;
		virtual uint32_t Unk_06(void*) override;
		virtual void	 Unk_07(void*) override;
		virtual uint32_t Unk_08(void*) override;
	public:
		SpellItem* Unk08;
	};
}
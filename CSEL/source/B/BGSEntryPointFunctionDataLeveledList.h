#pragma once
#include "../B/BGSEntryPointFunctionData.h"
#include "../T/TESLevItem.h"

namespace ConsoleRE
{
	class BGSEntryPointFunctionDataLeveledList : public BGSEntryPointFunctionData
	{
	public:
		BGSEntryPointFunctionDataLeveledList();
		virtual ~BGSEntryPointFunctionDataLeveledList();

		virtual uint32_t Unk_02(void*) override;
		virtual bool	 Unk_03(void*) override;
		virtual void	 Unk_04(void*) override;
		virtual void	 Unk_05(void*) override;
		virtual uint32_t Unk_06(void*) override;
		virtual void	 Unk_07(void*) override;
		virtual uint32_t Unk_08(void*) override;
	public:
		TESLevItem* Unk08;
	};
}
#pragma once

#include "../B/BSISoundDescriptor.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSSoundDescriptor;

	class BGSSoundDescriptorForm : public TESForm, public BSISoundDescriptor
	{
	public:
		static constexpr int TypeID = 128;
	public:
		~BGSSoundDescriptorForm() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool SetFormEditorID(const char* a_str) override;

		// add
		virtual uint32_t GetDescriptorType();
	public:
		BGSSoundDescriptor* soundDescriptor;
	};
	static_assert(sizeof(BGSSoundDescriptorForm) == 0x30);
}
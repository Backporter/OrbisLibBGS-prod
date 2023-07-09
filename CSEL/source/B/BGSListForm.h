#pragma once

#include "../B/BSTArray.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"

#include <stdio.h>
#include <functional>

namespace ConsoleRE
{
	class BGSListForm : public TESForm
	{
	public:
		static constexpr int TypeID = 91;
	public:
		~BGSListForm() override;

		// override (TESForm)
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		
		//
		void AddForm(TESForm* a_form);
		bool HasForm(const TESForm* a_form) const;
		bool HasForm(uint32_t a_formID) const;
		bool Visit(std::function<bool(TESForm*)> a_func);

		template <typename T>
		bool Visit(T& a_visitor)
		{
			TESForm* Form = NULL;
			uint32_t FormID = NULL;

			for (int i = 0; i < forms.size(); i++)
			{
				if (forms.Get(i, Form))
				{
					if (a_visitor.Accept(Form))
					{
						return true;
					}
				}
			}

			if (scriptAddedTempForms)
			{
				FormID = NULL;
				Form = NULL;
				
				for (int i = 0; i < scriptAddedTempForms->size(); i++)
				{
					scriptAddedTempForms->Get(i, FormID);
					Form = TESForm::GetFormFromID(FormID);
					if (Form)
					{
						if (a_visitor.Accept(Form))
						{
							return true;
						}
					}
				}
			}

			return false;
		}
	public:
		BSTArray<TESForm*>   forms;
		BSTArray<uint32_t>*  scriptAddedTempForms;
		uint32_t			 scriptAddedFormCount;
		uint32_t			 pad3C;
	};
	static_assert(sizeof(BGSListForm) == 0x40);
}
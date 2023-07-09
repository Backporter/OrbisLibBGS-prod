#include "../B/BGSListForm.h"

namespace ConsoleRE
{
	void BGSListForm::AddForm(TESForm* a_form)
	{
		using func_t = void(decltype(this), TESForm*);
		Relocation<func_t*> func("", 0x2644F0);
		return func(this, a_form);
	}

	bool BGSListForm::HasForm(const TESForm* a_form) const
	{
		if (!a_form) 
		{
			return false;
		}

		auto ptrIt = std::find(forms.begin(), forms.end(), a_form);
		if (ptrIt != forms.end()) 
		{
			return true;
		}

		if (!scriptAddedTempForms) 
		{
			return false;
		}

		auto idIt = std::find(scriptAddedTempForms->begin(), scriptAddedTempForms->end(), a_form->FormID);
		if (idIt != scriptAddedTempForms->end()) 
		{
			return true;
		}

		return false;
	}

	bool BGSListForm::HasForm(uint32_t a_formID) const
	{
		auto form = ConsoleRE::TESForm::GetFormFromID(a_formID);
		return HasForm(form);
	}

	bool BGSListForm::Visit(std::function<bool(TESForm*)> a_func)
	{
		for (auto form : forms)
		{
			if (a_func(form))
			{
				return true;
			}
		}

		if (scriptAddedTempForms)
		{
			for (auto id : *scriptAddedTempForms)
			{
				auto form = TESForm::GetFormFromID(id);
				if (form)
				{
					if (a_func(form))
					{
						return true;
					}
				}
			}
		}

		return false;
	}
}
#include "../Keyword/PapyrusExtKeyword.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSListForm.h"

namespace PapyrusExtFormList
{
	// I really hate doing this...
	using namespace ConsoleRE;

	class FormListArray
	{
	public:
		FormListArray(std::vector<TESForm*> * result) : m_result(result) { }

		bool Accept(TESForm * form)
		{
			m_result->push_back(form);
			return false;
		}

	private:
		std::vector<TESForm*>* m_result;
	};

	std::vector<TESForm*> ToArray(BGSListForm * list)
	{
		std::vector<TESForm*> result;
		
		if (!list)
			return result;

		FormListArray visitor(&result);
		list->Visit(visitor);

		return result;
	}

	void MergeForms(BGSListForm* list, std::vector<TESForm*> forms)
	{
		if (list)
		{
			for (uint32_t i = 0; i < forms.size(); i++)
			{
				TESForm* tempform = NULL;
				tempform = forms[i];
				
				if (tempform)
				{
					list->AddForm(tempform);
				}
			}
		}
	}

	bool RegisterFormList(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(ToArray),	BGSListForm, std::vector<TESForm*>>       ("ToArray",  "FormList", ToArray));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(MergeForms), BGSListForm, void, std::vector<TESForm*>> ("AddForms", "FormList", MergeForms));
		
		VM->SetCallableFromTasklets("FormList", "ToArray",  true);
		VM->SetCallableFromTasklets("FormList", "AddForms", true);

		return true;
	}
}
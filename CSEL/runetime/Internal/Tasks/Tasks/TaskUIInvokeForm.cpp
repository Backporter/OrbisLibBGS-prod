#include "../Tasks/TaskUIInvokeForm.h"

#include "../../../source/Hooks/ItemData/ItemData.h"

#include "../../../../source/U/UI.h"
#include "../../../../source/I/IMenu.h"
#include "../../../../source/G/GFxValue.h"
#include "../../../../source/V/VirtualMachine.h"
#include "../../../../source/I/IObjectHandlePolicy.h"

namespace Tasks
{
	TaskUIInvokeForm::TaskUIInvokeForm(const char* a_name, const char* a_target, uint64_t a_Form, uint32_t a_FormID) : 
		Tasklet("TaskUIInvokeForm", 0, Task::UI), 
		m_name(a_name), m_target(a_target)
	{
		auto hp = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->GetObjectHandlePolicy();
		m_Form = hp->GetHandleForObject(a_FormID, (const void*)a_Form);

		if (m_Form == hp->EmptyHandle())
		{
			m_FormID = -1;
		}
	}

	bool TaskUIInvokeForm::Invoke()
	{
		if (m_FormID == -1)
		{
			PRINT_POS;
			return false;
		}

		auto hp = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton()->GetObjectHandlePolicy();

		auto form = hp->GetObjectForHandle(m_FormID, m_Form);
		if (!form)
		{
			PRINT_POS;
			return false;
		}

		auto ui = ConsoleRE::UI::GetSingleton();
		if (!ui)
		{
			PRINT_POS;
			return false;
		}

		auto view = ui->GetMenu(m_name)->uiMovie;
		if (!view)
		{
			PRINT_POS;
			return false;
		}


		ConsoleRE::GFxValue args;
		view->CreateObject(&args);
		ItemData::form(&args, view, (ConsoleRE::TESForm*)form);

		view->Invoke(m_target.c_str(), NULL, &args, 1);
		return true;
	}
}

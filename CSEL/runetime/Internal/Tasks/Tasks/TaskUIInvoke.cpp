#include "../Tasks/TaskUIInvoke.h"

#include "../../../../source/I/IMenu.h"

namespace Tasks
{
	TaskUIInvoke::TaskUIInvoke(ConsoleRE::BSFixedString a_name, ConsoleRE::BSFixedString a_target) : 
		Tasklet("TaskUIInvoke", 0, Task::UI), 
		m_name(a_name), m_target(a_target)
	{}

	bool TaskUIInvoke::Invoke()
	{
		auto singleton = ConsoleRE::UI::GetSingleton();
		if (singleton)
		{
			auto menuEntry = singleton->menuMap.findT(m_name);
			if (menuEntry && menuEntry->menu && menuEntry->menu->uiMovie)
			{
				ConsoleRE::GFxValue* val = NULL;

				if (m_args.size() > 0)
				{
					val = m_args.data();
				}

				menuEntry->menu->uiMovie->Invoke(m_target.c_str(), NULL, val, m_args.size());
				return true;
			}
		}

		return false;
	}
}
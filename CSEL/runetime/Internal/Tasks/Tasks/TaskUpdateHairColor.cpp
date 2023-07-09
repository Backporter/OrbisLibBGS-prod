#include "../Tasks/TaskUpdateHairColor.h"

namespace Tasks
{
	TaskUpdateHairColor::TaskUpdateHairColor() : 
		Tasklet("TaskUpdateHairColor", 0, Task::Texture)
	{}

	bool TaskUpdateHairColor::Invoke()
	{
		ConsoleRE::PlayerCharacter::GetSingleton()->UpdateHairColor();
		return true;
	}
}

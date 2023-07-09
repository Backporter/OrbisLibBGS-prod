#include "../Tasks/TaskUpdateTintMasks.h"

#include "../../../../source/P/PlayerCharacter.h"

namespace Tasks
{
	TaskUpdateTintMasks::TaskUpdateTintMasks() : 
		Tasklet("TaskUpdateTintMasks", 0, Task::Texture)
	{}

	bool TaskUpdateTintMasks::Invoke()
	{
		ConsoleRE::PlayerCharacter::GetSingleton()->UpdateSkinColor();
		ConsoleRE::PlayerCharacter::UpdatePlayerTints();

		return true;
	}
}
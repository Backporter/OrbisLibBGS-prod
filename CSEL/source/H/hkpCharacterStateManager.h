#pragma once

#include "../H/hkReferencedObject.h"
#include "../H/hkpCharacterState.h"

namespace ConsoleRE
{
	class hkpCharacterStateManager : public hkReferencedObject
	{
	public:
		~hkpCharacterStateManager() override;
	public:
		hkpCharacterState* registeredState[hkpCharacterStateType::kTotal];
	};
	static_assert(sizeof(hkpCharacterStateManager) == 0x68);
}

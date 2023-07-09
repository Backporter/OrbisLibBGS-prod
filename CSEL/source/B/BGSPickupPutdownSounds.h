#pragma once

#include "../B/BaseFormComponent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BGSSoundDescriptorForm;

	class BGSPickupPutdownSounds : public BaseFormComponent
	{
		~BGSPickupPutdownSounds() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		BGSSoundDescriptorForm* pickupSound;
		BGSSoundDescriptorForm* putdownSound;
	};
	static_assert(sizeof(BGSPickupPutdownSounds) == 0x18);
}
#pragma once

#include "../H/hkRefPtr.h"
#include "../N/NiObject.h"

namespace ConsoleRE
{
	class hkReferencedObject;

	class bhkRefObject : public NiObject
	{
	public:
		~bhkRefObject() override;

		// override(NiObject)
		const NiRTTI* GetRTTI() const override;

		// add
		virtual void Unk_37();
		virtual void Unk_38();
	public:
		hkRefPtr<hkReferencedObject> referencedObject;
	};
	static_assert(sizeof(bhkRefObject) == 0x18);
}
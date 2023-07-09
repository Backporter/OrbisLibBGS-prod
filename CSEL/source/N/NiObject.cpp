#include "../../../OrbisUtil/include/Relocation.h"

#include "../N/NiObject.h"
#include "../N/NiStream.h"
#include "../N/NiRTTI.h"

namespace ConsoleRE
{
	const NiRTTI* NiObject::GetRTTI() const
	{
		Relocation<const NiRTTI*> rtti(__PRETTY_FUNCTION__, 0x37C7068);
		return rtti.get();
	}

	bool NiObject::RegisterStreamables(NiStream& a_stream)
	{
		return a_stream.RegisterSaveObject(this);
	}

	bool NiObject::IsEqual(NiObject* a_object)
	{
		return a_object != nullptr && strcmp(GetRTTI()->GetName(), a_object->GetRTTI()->GetName()) == 0;
	}

	void NiObject::ProcessClone(NiCloningProcess& a_cloning)
	{
		using func_t = void(NiObject* const, NiCloningProcess&);
		Relocation<func_t*> func("", 0xE8BF50);;
		return func(this, a_cloning);
	}

	void NiObject::CreateDeepCopy(NiPointer<NiObject>& a_object)
	{
		using func_t = void(NiObject* const, NiPointer<NiObject>&);
		Relocation<func_t*> func("", 0xE8C0D0);
		return func(this, a_object);
	}
}
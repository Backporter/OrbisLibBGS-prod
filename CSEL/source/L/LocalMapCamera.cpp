#include "../../../OrbisUtil/include/Relocation.h"

#include "../L/LocalMapCamera.h"

#include "../I/INISettingCollection.h"
#include "../N/NiCamera.h"

namespace ConsoleRE
{
	void LocalMapCamera::SetAreaBounds(NiPoint3& a_maxExtent, NiPoint3& a_minExtent)
	{
		auto ini = INISettingCollection::GetSingleton();
		auto fMapLocalHeight = ini ? ini->GetSetting("fMapLocalHeight:MapMenu") : nullptr;

		minExtent = a_minExtent;
		maxExtent = a_maxExtent;
		maxExtent.z += fMapLocalHeight ? fMapLocalHeight->GetFloat() : 0.0F;
	}

	void LocalMapCamera::SetDefaultStateInitialPosition(NiPoint3& a_position)
	{
		auto ini = INISettingCollection::GetSingleton();
		auto fMapLocalHeight = ini ? ini->GetSetting("fMapLocalHeight:MapMenu") : nullptr;

		defaultState->initialPosition = a_position;
		defaultState->initialPosition.z += fMapLocalHeight ? fMapLocalHeight->GetFloat() : 0.0F;
	}

	void LocalMapCamera::SetDefaultStateMinFrustumDimensions(float a_width, float a_height)
	{
		defaultState->minFrustumHalfWidth = a_width / 2.0F;
		defaultState->minFrustumHalfHeight = a_height / 2.0F;
	}

	void LocalMapCamera::SetDefaultStateTranslation(float a_x, float a_y, float a_z)
	{
		defaultState->translation.x = a_x - defaultState->initialPosition.x;
		defaultState->translation.y = a_y - defaultState->initialPosition.y;
		defaultState->translation.z = a_z - defaultState->initialPosition.z;
	}

	void LocalMapCamera::SetNorthRotation(float a_northRotation)
	{
		using func_t = decltype(&LocalMapCamera::SetNorthRotation);
		Relocation<func_t> func("", 0x157940);
		return func(this, a_northRotation);
	}

	void LocalMapCamera::Ctor(float a_zRotation)
	{
		using func_t = decltype(&LocalMapCamera::Ctor);
		Relocation<func_t> func("", 0x1576E0);
		return func(this, a_zRotation);
	}
}
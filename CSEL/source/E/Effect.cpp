#include "../E/Effect.h"
#include "../E/EffectSetting.h"

namespace ConsoleRE
{
	Effect::EffectItem::EffectItem() : magnitude(0.0f), area(0), duration(0)
	{}

	Effect::Effect() : effectItem(), pad0C(0), baseEffect(0), cost(0), pad1C(0)
	{}

	float Effect::GetMagnitude() const
	{
		if ((baseEffect->data.flags & 1024) != 0)
		{
			return 0.0f;
		}

		return effectItem.magnitude;
	}

	uint32_t Effect::GetArea() const
	{
		if ((baseEffect->data.flags & 2048) != 0)
		{
			return 0;
		}

		return effectItem.area;
	}

	uint32_t Effect::GetDuration() const
	{
		if ((baseEffect->data.flags & 512) != 0)
		{
			return 0;
		}

		return effectItem.duration;
	}


	void Effect::SetMagnitude(float a_val)
	{
		effectItem.magnitude = a_val;
	}

	void Effect::SetArea(uint32_t a_val)
	{
		effectItem.area = a_val;
	}
	
	void Effect::SetDuration(uint32_t a_val)
	{
		effectItem.duration = a_val;
	}
}
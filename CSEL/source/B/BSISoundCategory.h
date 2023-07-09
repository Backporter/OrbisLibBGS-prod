#pragma once

namespace ConsoleRE
{
	class BSISoundCategory
	{
	public:
		virtual ~BSISoundCategory();

		// add
		virtual bool                        Matches(const BSISoundCategory* a_category) const = 0;
		virtual float						GetCategoryVolume() const = 0;
		virtual void                        SetCategoryVolume(float a_value) = 0;
		virtual float						GetCategoryFrequency() const = 0;
		virtual void                        SetCategoryFrequency(float a_value) = 0;
		virtual uint16_t					GetCategoryAttenuation() const = 0;
		virtual void                        SetCategoryAttenuation(uint16_t a_value) = 0;
		virtual void                        Unk_08(void) = 0;
		virtual void                        Unk_09(void) = 0;
		virtual void                        Unk_0A(void) = 0;
		virtual void                        Unk_0B(void) = 0;
	public:
	};
	static_assert(sizeof(BSISoundCategory) == 0x8);
}
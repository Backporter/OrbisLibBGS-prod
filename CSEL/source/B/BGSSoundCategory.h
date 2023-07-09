#pragma once

#include "../B/BSISoundCategory.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class BGSSoundCategory : public TESForm, public TESFullName, public BSISoundCategory
	{
	public:
		static constexpr int TypeID = 130;
	public:
		~BGSSoundCategory() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;

		// override (BGSSoundCategory)
		bool          Matches(const BSISoundCategory* a_category) const override;
		float         GetCategoryVolume() const override;
		void          SetCategoryVolume(float a_value) override;
		float         GetCategoryFrequency() const override;
		void          SetCategoryFrequency(float a_value) override;
		uint16_t	  GetCategoryAttenuation() const override;
		void          SetCategoryAttenuation(uint16_t a_value) override;
	public:
		uint32_t			flags;
		uint32_t			unk3C;
		BGSSoundCategory*	parentCategory;
		uint16_t            unk48;
		uint16_t            attenuation;
		uint16_t            staticMult;
		uint16_t            defaultMenuValue;
		float               volumeMult;
		float               frequencyMult;
	};
	static_assert(sizeof(BGSSoundCategory) == 0x58);
}
#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	struct LoadNIFData
	{
	public:
		TESBoundObject* loadNIF;
		float           initialScale;
		int16_t			rotationConstraints[3];
		int16_t			rotationOffsetConstraints[2];
		uint16_t		pad16;
		float           initialTranslationOffset[3];
		uint32_t		pad24;
		TESModel        cameraPath;
	};

	class TESLoadScreen : public TESForm 
	{
	public:
		static constexpr int TypeID = 81;
	public:
		~TESLoadScreen() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		TESCondition  conditions;
		LoadNIFData*  loadNIFData;
		BSFixedString loadingText;
	};
}
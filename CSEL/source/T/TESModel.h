#pragma once

#include "../B/BSFixedString.h"
#include "../B/BaseFormComponent.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESModelTextureSwap;

	class TESModel : public BaseFormComponent
	{
	public:
		~TESModel() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		virtual const char*				GetModel();
		virtual void					SetModel(const char*);
		virtual TESModelTextureSwap*	GetAsModelTextureSwap();
	public:
		BSFixedString model;
		void*		  textures;
		uint32_t*	  addons;
		uint16_t	  numTextures;
		uint16_t	  numAddons;
	};
	static_assert(sizeof(TESModel) == 0x28);
}
#pragma once

#include "../../../OrbisUtil/include/Relocation.h"
#include <stdint.h>

namespace ConsoleRE
{
	class TESForm;

	class IFormFactory
	{
	public:
		virtual ~IFormFactory();
		
		// add
		virtual TESForm*			 CreateImpl() = 0;
		virtual const char*          GetFormName() const = 0;
		virtual uint32_t             GetFormType() const = 0;
		virtual const char*          GetObjectName() const;
		virtual uint32_t			 GetObjectType() const;
		virtual uint32_t			 GetObjectCategory() const;

		static void GetFormFactories(IFormFactory**& a_dst, bool& a_inited)
		{
			struct Factories
			{
				IFormFactory* data[138];
			};
			
			Relocation<Factories*>	formFactories("", 0x20C5C00);
			Relocation<bool*>		formFactoriesInitialized("", 0x20C6050);
			
			a_dst		= formFactories->data;
			a_inited	= *formFactoriesInitialized;
		}

		static IFormFactory* GetFormFactoryByType(uint32_t a_formType)
		{
			IFormFactory**	formFactories;
			bool			formFactoriesInitialized;

			GetFormFactories(formFactories, formFactoriesInitialized);
			return formFactoriesInitialized ? formFactories[a_formType] : 0;
		}
	public:
	};
	static_assert(sizeof(IFormFactory) == 0x8);
}
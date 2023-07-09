#pragma once

#include "../I/IFormFactory.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	template <class T, uint32_t FormID>
	class ConcreteFormFactory : public IFormFactory
	{
	public:
		~ConcreteFormFactory() override;
		
		// override
		TESForm*	CreateImpl() override;
		const char* GetFormName() const override;   
		uint32_t    GetFormType() const override;
	public:
		const char* m_name;
	};
	static_assert(sizeof(ConcreteFormFactory<TESForm, 0>) == 0x10);
}
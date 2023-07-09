#pragma once

#include "../QueryInterface/QueryInterface.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			class VirtualMachine;
		}
	}
}

namespace Interface
{
	class PapyrusInterface : public QueryInterface
	{
	public:		
		// Interface ID
		static constexpr int TypeID = 1;

		// Interface Version
		static constexpr int Version = 1;
		
		// 
		using RegisterFunctions_t = bool(ConsoleRE::BSScript::Internal::VirtualMachine*);
	public:
		PapyrusInterface() = default;
		~PapyrusInterface() override = default;
		
		// override (QueryInterface)
		int	GetInterfaceVersion() override;
		
		// add
		virtual void RegisterPapyrusFunctions(RegisterFunctions_t*);
		virtual void UnregisterPapyrusFunction(RegisterFunctions_t*);
	};
	static_assert(sizeof(PapyrusInterface) == 0x8);
}
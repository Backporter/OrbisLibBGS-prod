#include "PapyrusInterface.h"

#include "../../../source/Hooks/Papyrus/PapyrusExt.h"

namespace Interface
{
	int	PapyrusInterface::GetInterfaceVersion() 
	{ 
		return Version; 
	}

	void PapyrusInterface::RegisterPapyrusFunctions(RegisterFunctions_t* a_func) 
	{ 
		return Papyrus::Plugin::RegisterPluginFunctions(a_func); 
	}

	void PapyrusInterface::UnregisterPapyrusFunction(RegisterFunctions_t* a_func) 
	{ 
		return Papyrus::Plugin::UnregisterPluginFunctions(a_func); 
	}
}
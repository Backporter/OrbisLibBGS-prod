#include "TrampolineInterface.h"

#include "../../../../../OrbisUtil/include/Trampoline.h"
#include "../../../../../OrbisUtil/include/Logger.h"

namespace Interface
{
	int	TrampolineInterface::GetInterfaceVersion()															
	{ 
		return Version;
	}

	void* TrampolineInterface::Allocate(size_t a_handle, size_t a_size, bool a_branchPool)
	{		
		if (a_branchPool)
			return xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).allocatePlugin(a_handle, a_size);
		else
			return xUtilty::Trampoline::get(xUtilty::Trampoline::kLocal).allocatePlugin(a_handle, a_size);
	}
	
	void TrampolineInterface::Restore(size_t a_pluginHandle, void* a_allocated, size_t a_allocatedLength)
	{
		// return xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).restorePlugin(a_pluginHandle, a_allocated, a_allocatedLength);
	}
	
	void* TrampolineInterface::GetTrampoline()																
	{ 
		auto ret = &xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);
		return (void*)ret;
	}
}
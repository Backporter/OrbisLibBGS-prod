#pragma once

#include "../QueryInterface/QueryInterface.h"

namespace Interface
{
	class TrampolineInterface : public QueryInterface
	{
	public:
		// Interface ID
		static constexpr int TypeID = 5;
		
		// Interface Version
		static constexpr int Version = 1;
	public:
		TrampolineInterface() = default;
		~TrampolineInterface() override = default;
		
		// override (QueryInterface)
		int	GetInterfaceVersion() override;
		
		// add
		virtual void*	Allocate(size_t a_pluginHandle, size_t a_size, bool a_branchPool = true);
		virtual void	Restore(size_t a_pluginHandle, void* a_allocated, size_t a_allocatedLength);

		// returns the internal trampoline, do not use.
		virtual void*	GetTrampoline();

		void* Allocate(size_t a_size) 
		{ 
			return Allocate(QueryHandle(), a_size, true); 
		}

		void Restore(void* a_allocated, size_t a_allocatedLength) 
		{ 
			return Restore(QueryHandle(), a_allocated, a_allocatedLength); 
		}
	};
	static_assert(sizeof(TrampolineInterface) == 0x8);
}
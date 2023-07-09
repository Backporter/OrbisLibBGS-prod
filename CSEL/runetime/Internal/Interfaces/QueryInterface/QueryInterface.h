#pragma once

#include <stdio.h>
#include <stdint.h>

namespace Interface
{
	//
	void* InternalQueryInterfaceFromID(int32_t a_interfaceType);
	
	template <typename T>
	T* InternalQueryInterfaceFromID(int32_t a_interfaceType)
	{
		return static_cast<T*>(InternalQueryInterfaceFromID(a_interfaceType));
	}
	//

	class QueryInterface
	{
	public:
		// Interface ID
		static constexpr size_t TypeID = 0;
		
		// Interface Version
		static constexpr size_t Version = 1;
	public:
		QueryInterface() = default;
		virtual ~QueryInterface() = default;

		// add
		virtual size_t	GetModuleVersion();
		virtual int		GetInterfaceVersion();
		virtual void*	QueryInterfaceFromID(uint32_t);
		virtual void*	QueryEventSource(uint32_t);
		virtual size_t	QueryHandle();
	};
	static_assert(sizeof(QueryInterface) == 0x8);
}
#pragma once

#include "../I/IPackageData.h"

#include <type_traits>

namespace ConsoleRE
{
	template <class T>
	class BGSNamedPackageData : public T
	{
	public:
		static_assert(std::is_base_of<IPackageData, T>::value);

		union Data
		{
			bool          b;
			uint32_t	  i;
			float         f;
			void*         p;
		};
		static_assert(sizeof(Data) == 0x8);
	public:
		// override (IPackageData)
		// ...
	public:
		Data data;
	};
}
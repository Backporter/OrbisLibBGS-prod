#pragma once

#include "../A/Array.h"
#include "../B/BSTSmartPointer.h"
#include "../P/PackUnpack.h"
#include "../T/TypeInfo.h"
#include "../V/Variable.h"
#include "../V/VirtualMachine.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		template <class T, class U, std::enable_if_t<is_array_v<U>, int>>
		void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetNone();
		
			auto vm = Internal::VirtualMachine::GetSingleton();
			if (!vm)
			{
				assert(false);
				return;
			}
		
			BSTSmartPointer<Array> s_array;
			TypeInfo			   s_typeinfo(GetRawType<typename U::value_type>());
			
			if (!vm->CreateArray(s_typeinfo, static_cast<uint32_t>(a_src.size()), s_array) || !s_array)
			{
				assert(false);
				return;
			}
		
			auto it = a_src.begin();
			auto end = a_src.end();
			uint32_t i = 0;
			
			while (it != end)
			{
				if constexpr (std::is_same<U, std::vector<bool>>::value)
				{
					(*s_array)[i++].Pack(static_cast<bool>(*it));
				}
				else
				{
					(*s_array)[i++].Pack(*it);
				}
				++it;
			}
		
			a_dst->SetArray(std::move(s_array));
		}
		
		template <class T, std::enable_if_t<is_array_v<T>, int>>
		T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
		
			std::remove_const_t<T> container;
			if (a_src->IsNoneObject() || a_src->IsNoneArray())
			{
				return container;
			}
		
			auto s_array = a_src->GetArray();
			if (!s_array)
			{
				return container;
			}
		
			for (auto& elem : *s_array)
			{
				container.push_back(elem.Unpack<typename T::value_type>());
			}
		
			return container;
		}
	}
}
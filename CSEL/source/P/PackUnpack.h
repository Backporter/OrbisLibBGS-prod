#pragma once

#include "../../../OrbisUtil/include/type_traits.h"

#include "../B/BSTSmartPointer.h"
#include "../T/TypeTraits.h"
#include "../V/Variable.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		TypeInfo::RawType GetRawTypeFromVMType(uint32_t a_typeID);
		void			  BindID(BSTSmartPointer<Object>& a_objectPtr, const void* a_src, uint32_t a_typeID);
		void			  PackHandle(Variable* a_dst, const void* a_src, uint32_t a_typeID);
		void*			  UnpackHandle(Variable* a_src, uint32_t a_typeID);

		template <class T, std::enable_if_t<std::is_builtin_convertible_v<T>, int> = 0>
		inline TypeInfo::RawType GetRawType()
		{
			return vm_type_v<T>;
		}

		template <class T, std::enable_if_t<is_form_pointer_v<T> || is_alias_pointer_v<T> || is_active_effect_pointer_v<T>, int> = 0>
		inline TypeInfo::RawType GetRawType()
		{
			return GetRawTypeFromVMType(std::decay_pointer_t<T>::TypeID);
		}

		//
		template <class T, std::enable_if_t<std::disjunction_v<is_array<T>, is_reference_wrapper<T>>, int> = 0>
		inline TypeInfo::RawType GetRawType()
		{
			using value_type = typename T::value_type;
			if constexpr (std::is_builtin_convertible_v<value_type>) 
			{
				return (TypeInfo::RawType) ((size_t)vm_type_v<T> + (size_t)TypeInfo::RawType::kNoneArray);
			}
			else if constexpr (is_form_pointer_v<value_type>) 
			{
				return (TypeInfo::RawType) ((size_t)GetRawTypeFromVMType(static_cast<uint32_t>(unwrapped_type_t<T>::TypeID)) + (size_t)TypeInfo::RawType::kObject);
			}
			else if constexpr (is_alias_pointer_v<value_type> || is_active_effect_pointer_v<value_type>) 
			{
				return (TypeInfo::RawType) ((size_t)GetRawTypeFromVMType(static_cast<uint32_t>(unwrapped_type_t<T>::TypeID)) + (size_t)TypeInfo::RawType::kObject);
			}
			else 
			{
				static_assert(sizeof(T) && false);
			}
		}
		//

		template <class T, class U = std::decay_t<T>, std::enable_if_t<std::is_string_convertible_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetString(std::forward<T>(a_src));
		}

		template <class T, class U = std::decay_t<T>, std::enable_if_t<std::is_signed_integral_convertible_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetInt(static_cast<int32_t>(std::forward<T>(a_src)));
		}

		template <class T, class U = std::decay_t<T>, std::enable_if_t<std::is_unsigned_integral_convertible_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetUInt(static_cast<uint32_t>(std::forward<T>(a_src)));
		}

		template <class T, class U = std::decay_t<T>, std::enable_if_t<std::is_floating_point_convertible_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetFloat(static_cast<float>(std::forward<T>(a_src)));
		}
		 
		template <class T, class U = std::decay_t<T>, std::enable_if_t<std::is_boolean_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			assert(a_dst);
			a_dst->SetBool(static_cast<bool>(std::forward<T>(a_src)));
		}

		template <class T, class U = std::decay_t<T>, std::enable_if_t<is_form_pointer_v<U> || is_alias_pointer_v<U> || is_active_effect_pointer_v<U>, int> = 0>
		inline void PackValue(Variable* const a_dst, T&& a_src)
		{
			PackHandle(a_dst, std::forward<T>(a_src), static_cast<uint32_t>(std::decay_pointer_t<U>::TypeID));
		}

		//
		template <class T, class U = std::decay_t<T>, std::enable_if_t<is_array_v<U>, int> = 0>
		void PackValue(Variable* const a_dst, T&& a_src);
		//

		template <class T, std::enable_if_t<is_static_base_pointer_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			return static_cast<T>(nullptr);
		}

		template <class T, std::enable_if_t<std::is_string_convertible_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
			return T{ a_src->GetString() };
		}

		template <class T, std::enable_if_t<std::is_signed_integral_convertible_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
			return static_cast<T>(a_src->GetInt());
		}

		template <class T, std::enable_if_t<std::is_unsigned_integral_convertible_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
			return static_cast<T>(a_src->GetUInt());
		}

		template <class T, std::enable_if_t<std::is_floating_point_convertible_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
			return static_cast<T>(a_src->GetFloat());
		}

		template <class T, std::enable_if_t<std::is_boolean_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			assert(a_src);
			return static_cast<T>(a_src->GetBool());
		}

		template <class T, std::enable_if_t<is_form_pointer_v<T> || is_alias_pointer_v<T> || is_active_effect_pointer_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			return static_cast<T>(UnpackHandle(a_src, static_cast<uint32_t>(std::decay_pointer_t<T>::TypeID)));
		}

		//
		template <class T, std::enable_if_t<is_array_v<T>, int> = 0>
		T UnpackValue(Variable* const a_src);

		template <class T, std::enable_if_t<is_reference_wrapper_v<T>, int> = 0>
		inline T UnpackValue(Variable* const a_src)
		{
			return T{ a_src };
		}
		//

		template <typename T>
		inline void Variable::Pack(T&& a_src)  { return PackValue<T>(this, std::forward<T>(a_src)); }

		template <typename T>
		inline T Variable::Unpack()			   { return UnpackValue<T>(this); }
	}
}
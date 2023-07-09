#pragma once

// needed for C++17 type_traits.
#include "../../../OrbisUtil/include/type_traits.h"

// // needed for C++-14 type_traits.
#include <type_traits>
#include <tuple>

//
#include "../A/ActiveEffect.h"
#include "../B/BGSBaseAlias.h"
#include "../B/BSFixedString.h"
#include "../T/TypeInfo.h"

#include "../T/TESForm.h"
#include "../R/ReferenceArray.h"

namespace ConsoleRE
{
	struct StaticFunctionTag
	{};

	namespace BSScript
	{
		template <class T>
		struct is_string : std::is_string<std::remove_cv_t<T>, BSFixedString>
		{
		};

		template <class T>
		inline constexpr bool is_string_v = std::is_string<T, BSFixedString>::value;
	}

	namespace BSScript
	{
		template <class>
		struct _is_reference_wrapper : std::false_type
		{};

		template <class T>
		struct _is_reference_wrapper<reference_array<T>> : std::true_type
		{};

		template <class T>
		struct is_reference_wrapper : _is_reference_wrapper<std::remove_cv_t<T>>
		{};

		template <class T>
		struct is_form : std::is_base_of<ConsoleRE::TESForm, std::remove_cv_t<T>>
		{ 
		};

		template <class T>
		struct is_form_pointer : std::conjunction<is_form<std::remove_pointer_t<T>>, std::is_pointer<T>>
		{
		};

		template <class T>
		struct is_alias : std::is_base_of<ConsoleRE::BGSBaseAlias, std::remove_cv_t<T>>
		{
		};

		template <class T>
		struct is_alias_pointer : std::conjunction<is_alias<std::remove_pointer_t<T>>, std::is_pointer<T>>
		{
		};

		template <class T>
		struct is_active_effect : std::is_base_of< ConsoleRE::ActiveEffect, std::remove_cv_t<T>>
		{
		};

		template <class T>
		struct is_active_effect_pointer : std::conjunction<is_active_effect<std::remove_pointer_t<T>>, std::is_pointer<T>>
		{
		};

		template <class T>
		struct is_static_base : std::is_same<std::decay_pointer_t<T>, StaticFunctionTag>
		{
		};

		template <class T>
		struct is_static_base_pointer : std::conjunction<is_static_base<T>, std::is_pointer<T>>
		{
		};

		template <class T>
		struct is_valid_base : std::disjunction<is_static_base_pointer<T>, is_form_pointer<T>, is_alias_pointer<T>, is_active_effect_pointer<T>>
		{
		};

#pragma region
		template <class T>
		struct is_not_reference : std::negation<std::is_reference<T>>
		{};

		template <class T>
		struct is_not_pointer : std::negation<std::is_pointer<T>>
		{};

		template <class, class = void>
		struct defines_value_type :
			std::false_type
		{};

		template <class T>
		struct defines_value_type<T, std::void_t<typename T::value_type>> :
			std::true_type
		{};

		template <class, class = void>
		struct defines_size_type :
			std::false_type
		{};

		template <class T>
		struct defines_size_type<T, std::void_t<typename T::size_type>> :
			std::true_type
		{};

		template <class, class = void>
		struct defines_iterator :
			std::false_type
		{};

		template <class T>
		struct defines_iterator<T, std::void_t<typename T::iterator>> :
			std::true_type
		{};

		template <class, class = void>
		struct implements_begin :
			std::false_type
		{};

		template <class T>
		struct implements_begin<T, std::enable_if_t<std::is_same_v<typename T::iterator, decltype(std::declval<T>().begin())>>> :
			std::true_type
		{};

		template <class, class = void>
		struct implements_end :
			std::false_type
		{};

		template <class T>
		struct implements_end<T, std::enable_if_t<std::is_same_v<typename T::iterator, decltype(std::declval<T>().end())>>> :
			std::true_type
		{};

		template <class, class = void>
		struct implements_push_back :
			std::false_type
		{};

		template <class T>
		struct implements_push_back<T, std::void_t<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>> :
			std::true_type
		{};

		template <class T>
		struct _is_array :
			std::conjunction<
			std::negation<
			std::is_string_convertible<T>>,
			std::is_default_constructible<T>,
			std::is_destructible<T>,
			is_not_reference<T>,
			is_not_pointer<T>,
			defines_value_type<T>,
			defines_size_type<T>,
			defines_iterator<T>,
			implements_begin<T>,
			implements_end<T>,
			// implements_size<T>,
			implements_push_back<T>>
		{};

		template <>
		struct _is_array<std::vector<bool>> :
			std::true_type
		{};

		template <class T>
		struct is_array : _is_array<std::remove_cv_t<T>>
		{};

		template <class T>
		inline constexpr bool is_not_reference_v = is_not_reference<T>::value;

		template <class T>
		inline constexpr bool is_not_pointer_v = is_not_pointer<T>::value;

		template <class T>
		inline constexpr bool defines_value_type_v = defines_value_type<T>::value;

		template <class T>
		inline constexpr bool defines_size_type_v = defines_size_type<T>::value;

		template <class T>
		inline constexpr bool defines_iterator_v = defines_iterator<T>::value;

		template <class T>
		inline constexpr bool implements_begin_v = implements_begin<T>::value;

		template <class T>
		inline constexpr bool implements_end_v = implements_end<T>::value;

		template <class T>
		inline constexpr bool implements_push_back_v = implements_push_back<T>::value;

		template <class T>
		inline constexpr bool is_array_v = is_array<T>::value;

		//
		template <class T, class = void>
		struct _unwrapped_type
		{
			using type = std::decay_pointer_t<T>;
		};

		template <class T>
		struct _unwrapped_type<T, std::enable_if_t<std::disjunction_v<is_array<T>, is_reference_wrapper<T>>>>
		{
			using type = std::decay_pointer_t<typename T::value_type>;
		};

		template <class T>
		struct unwrapped_type :
			_unwrapped_type<
			std::remove_cv_t<T>>
		{};

		template <class T>
		using unwrapped_type_t = typename unwrapped_type<T>::type;
#pragma endregion

		template <class T>
		inline constexpr bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

		template <class T>
		inline constexpr bool is_form_v = is_form<T>::value;

		template <class T>
		inline constexpr bool is_form_pointer_v = is_form_pointer<T>::value;

		template <class T>
		inline constexpr bool is_alias_v = is_alias<T>::value;

		template <class T>
		inline constexpr bool is_alias_pointer_v = is_alias_pointer<T>::value;

		template <class T>
		inline constexpr bool is_active_effect_v = is_active_effect<T>::value;

		template <class T>
		inline constexpr bool is_active_effect_pointer_v = is_active_effect_pointer<T>::value;

		template <class T>
		inline constexpr bool is_static_base_v = is_static_base<T>::value;

		template <class T>
		inline constexpr bool is_static_base_pointer_v = is_static_base_pointer<T>::value;
	
		template <class T>
		inline constexpr bool is_valid_base_v = is_valid_base<T>::value;
	}

	namespace BSScript
	{
		template <TypeInfo::RawType V>
		struct vm_type_constant : std::integral_constant<TypeInfo::RawType, V>
		{};

		template <class, class = void>
		struct _vm_type;

		template <>
		struct _vm_type<void> : vm_type_constant<TypeInfo::RawType::kNone>
		{};

		template <class T>
		struct _vm_type<T, std::enable_if_t<std::is_string_convertible_v<T>>> : vm_type_constant<TypeInfo::RawType::kString>
		{};

		template <class T>
		struct _vm_type<T, std::enable_if_t<std::is_integral_convertible_v<T>>> : vm_type_constant<TypeInfo::RawType::kInt>
		{};

		template <class T>
		struct _vm_type<T, std::enable_if_t<std::is_floating_point_convertible_v<T>>> : vm_type_constant<TypeInfo::RawType::kFloat>
		{};

		template <class T>
		struct _vm_type<T, std::enable_if_t<std::is_boolean_v<T>>> : vm_type_constant<TypeInfo::RawType::kBool>
		{};

		template <class T>
		struct vm_type : _vm_type<unwrapped_type_t<T>>
		{};

		// template <class T>
		// struct vm_type : _vm_type<std::decay_t<std::remove_pointer_t<std::remove_cv_t<T>>>>
		// {};

		template <class T>
		inline constexpr TypeInfo::RawType vm_type_v = vm_type<T>::value;
	}
}
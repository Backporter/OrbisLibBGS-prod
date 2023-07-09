#pragma once

// needed for wchar_t_t
#include "../../../OrbisUtil/include/Types.h"

#include "../G/GMatrix3D.h"
#include "../G/GMemory.h"
#include "../G/GNewOverrideBase.h"
#include "../G/GString.h"

#include <math.h>
#include <stdint.h>

namespace ConsoleRE
{
	class GFxMovieRoot;

	namespace GFxValueImpl
	{
		template <class>
		struct _is_integer :
			std::false_type
		{};

		template <>
		struct _is_integer<unsigned char> :
			std::true_type
		{};

		template <>
		struct _is_integer<char> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed char> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned short> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed short> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned int> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed int> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned long> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed long> :
			std::true_type
		{};

		template <>
		struct _is_integer<unsigned long long> :
			std::true_type
		{};

		template <>
		struct _is_integer<signed long long> :
			std::true_type
		{};

		template <class T>
		struct is_integer :
			std::conditional_t<std::is_enum_v<T>, std::true_type, _is_integer<std::remove_cv_t<T>>>
		{};

		template <class T>
		inline constexpr bool is_integer_v = is_integer<T>::value;
	}

	class GFxValue
	{
	public:
		enum class ValueType
		{
			//
			kUndefined		= 0x0,
			kNull			= 0x1,
			kBoolean		= 0x2,
			kNumber			= 0x3,
			kString			= 0x4,
			kStringW		= 0x5,
			kObject			= 0x6,
			kArray			= 0x7,
			kDisplayObject	= 0x8,

			//
			kManagedBit = 1 << 6,
			kConvertBit = 1 << 7,
			kValueMask	= 0x0F,

			//
			kTypeMask		= kConvertBit | kValueMask,
			kConvertBoolean = kConvertBit | kBoolean,
			kConvertNumber	= kConvertBit | kNumber,
			kConvertString	= kConvertBit | kString,
			kConvertStringW = kConvertBit | kStringW
		};

		class DisplayInfo
		{
		public:
			enum Flag : uint32_t
			{
				kNone = 0,
				kX = 1 << 0,
				kY = 1 << 1,
				kRotation = 1 << 2,
				kXScale = 1 << 3,
				kYScale = 1 << 4,
				kAlpha = 1 << 5,
				kVisible = 1 << 6,
				kZ = 1 << 7,
				kXRotation = 1 << 8,
				kYRotation = 1 << 9,
				kZScale = 1 << 10,
				kFOV = 1 << 11,
				kPerspMatrix3D = 1 << 12,
				kViewMatrix3D = 1 << 13
			};
		public:
			DisplayInfo() = default;
			DisplayInfo(double a_x, double a_y);
			DisplayInfo(double a_rot);
			DisplayInfo(bool a_visable);
			
			//
			void						   Clear();
			double						   GetAlpha() const;
			double						   GetFOV() const;
			double						   GetRotation() const;
			bool						   GetVisible() const;
			const GMatrix3D*			   GetPerspectiveMatrix3D() const;
			const GMatrix3D*			   GetViewMatrix3D() const;
			double						   GetX() const;
			double						   GetY() const;
			double						   GetZ() const;
			double						   GetXRotation() const;
			double						   GetYRotation() const;
			double						   GetXScale() const;
			double						   GetYScale() const;
			double						   GetZScale() const;
			bool						   IsFlagSet(uint32_t a_flag) const;
			void                           Initialize(uint32_t a_varsSet, double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale, double a_fov, const GMatrix3D* a_viewM, const GMatrix3D* a_perspM);
			void                           SetVisible(bool a_visible);
			void                           SetPerspectiveMatrix3D(const GMatrix3D* a_mat);
			void                           Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible);
			void                           Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale);
			void                           SetViewMatrix3D(const GMatrix3D* a_mat);
			void                           SetAlpha(double a_alpha);
			void                           SetFOV(double a_fov);
			void                           SetPosition(double a_x, double a_y);
			void                           SetRotation(double a_degrees);
			void                           SetScale(double a_xScale, double a_yScale);
			void                           SetX(double a_x);
			void                           SetXRotation(double a_degrees);
			void                           SetXScale(double a_xScale);
			void                           SetY(double a_y);
			void                           SetYRotation(double a_degrees);
			void                           SetYScale(double a_yScale);
			void                           SetZ(double a_z);
			void                           SetZScale(double a_zScale);
		protected:
			void						   SetFlags(uint16_t a_flags);
			void						   ClearFlags(uint16_t a_flags);
		public:
			double		_x = 0.0;
			double		_y = 0.0;
			double		_rotation = 0.0;
			double		_xScale = 0.0;
			double		_yScale = 0.0;
			double		_alpha = 0.0;
			bool		_visible = false;
			uint8_t		_pad31 = 0;
			uint16_t	_pad32 = 0;
			uint32_t	_pad34 = 0;
			double		_z = 0.0;
			double		_xRotation = 0.0;
			double		_yRotation = 0.0;
			double		_zScale = 0.0;
			double		_fov = 0.0;
			GMatrix3D	_viewMatrix3D;
			GMatrix3D	_perspMatrix3D;
			uint32_t	_flags = 0;
			uint32_t	_padD4 = 0;
		};
		static_assert(sizeof(DisplayInfo) == 0xE8);

		class ObjectInterface : public GNewOverrideBase<326>
		{
		public:
			ObjectInterface(GFxMovieRoot* a_mvoieRoot);

			//
			void		ObjectAddRef(GFxValue* a_value, void* a_obj);
			void		ObjectRelease(GFxValue* a_value, void* a_obj);
			bool		HasMember(void* a_data, const char* a_name, bool a_isDisplayObj);
			bool		GetMember(void* a_data, const char* a_name, GFxValue* a_value, bool a_isDisplayObj);
			bool		SetMember(void* a_data, const char* a_name, GFxValue* a_value, bool a_isDisplayObj);
			bool		Invoke(void* a_data, GFxValue* a_result, const char* a_name, GFxValue* a_args, uint32_t a_numArgs, bool a_isDisplayObj);
			bool		DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObj);
			uint32_t	GetArraySize(void* a_data);
			bool		SetArraySize(void* a_data, uint32_t a_size);
			bool		GetElement(void* a_data, uint32_t a_idx, GFxValue* a_value);
			bool		SetElement(void* a_data, uint32_t a_idx, const GFxValue& a_val);
			bool		PushBack(void* a_data, const GFxValue& a_value);
			bool		RemoveElements(void* a_data, uint32_t a_idx, int32_t a_count);
			bool		GetDisplayInfo(void* a_data, DisplayInfo* a_displayInfo);
			bool		SetDisplayInfo(void* a_data, const DisplayInfo& a_displayInfo);
			bool		SetText(void* a_data, const char* a_text, bool a_isHTML);
			bool		AttachMovie(void* a_data, GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, int32_t a_depth, const GFxValue* a_initObj);
			bool		GotoAndPlay(void* a_data, const char* a_frame, bool a_stop);
			bool		IsSameContext(const ObjectInterface* a_rhs) const;
		public:
			GFxMovieRoot* m_movieRoot;
		};
	public:
		GFxValue();
		GFxValue(ValueType a_type);
		GFxValue(double d);
		GFxValue(bool b);
		GFxValue(const char* string);
		GFxValue(const wchar_t_t* wstring);
		GFxValue(const GFxValue& rhs);

		template <class T, std::enable_if_t<GFxValueImpl::is_integer_v<T>, int> = 0>
		inline GFxValue(T a_val) : GFxValue(static_cast<double>(a_val))
		{}

		~GFxValue();

		//
		GFxValue& operator=(std::nullptr_t);
		GFxValue& operator=(double a_rhs);
		GFxValue& operator=(bool a_rhs);
		GFxValue& operator=(const char* a_rhs);
		GFxValue& operator=(const wchar_t_t* a_rhs);
		GFxValue& operator=(const GFxValue& a_rhs);
		GFxValue& operator=(GFxValue&& a_rhs);

		template <class T, std::enable_if_t<GFxValueImpl::is_integer_v<T>, int> = 0>
		inline GFxValue& operator=(T a_val)
		{
			return*this = static_cast<double>(a_val);
		}

		bool operator==(const GFxValue& a_rhs) const;

		GString 			ToString() const;
		ValueType			GetType() const;
		bool				IsUndefined() const;
		bool				IsNull() const;
		bool				IsBool() const;
		bool				IsNumber() const;
		bool				IsString() const;
		bool				IsStringW() const;
		bool				IsObject() const;
		bool				IsArray() const;
		bool				IsDisplayObject() const;
		bool				GetBool() const;
		double				GetNumber() const;
		std::ptrdiff_t		GetSInt() const;
		std::size_t			GetUInt() const;
		const char*			GetString() const;
		const wchar_t_t*	GetStringW() const;

		void				SetUndefined();
		void				SetNull();
		void				SetBoolean(bool a_val);
		void				SetNumber(double a_val);
		void				SetString(const char* a_str);
		void				SetStringW(const wchar_t_t* a_str);

		bool				HasMember(const char* a_name) const;
		bool				GetMember(const char* a_name, GFxValue* a_val) const;
		bool				SetMember(const char* a_name, GFxValue* a_val);
		bool				Invoke(const char* a_name, GFxValue* a_result, GFxValue* a_args, uint32_t a_numArgs);
		bool				Invoke(const char* a_name, GFxValue* a_result);
		bool				DeleteMember(const char* name);

		template <size_t N>
		inline bool Invoke(const char* a_name, const std::array<GFxValue, N>& a_args)
		{
			return Invoke(a_name, nullptr, a_args);
		}

		template <size_t N>
		inline bool Invoke(const char* a_name, GFxValue* a_result, const std::array<GFxValue, N>& a_args)
		{
			return Invoke(a_name, a_result, a_args.data(), a_args.size());
		}

		//
		uint32_t	GetArraySize() const;
		bool		SetArraySize(uint32_t a_size);
		bool		GetElement(uint32_t a_idx, GFxValue* a_value) const;
		bool		SetElement(uint32_t a_idx, const GFxValue& a_val);
		bool		PushBack(const GFxValue& a_value);
		bool        RemoveElements(uint32_t a_idx, int32_t a_count = -1);
		bool        RemoveElement(uint32_t a_idx);
		bool        ClearElements();

		bool		GetDisplayInfo(DisplayInfo* a_info) const;
		bool		SetDisplayInfo(const DisplayInfo& a_info);

		bool		SetText(const char* a_text);
		bool		SetTextHTML(const char* a_html);

		bool		AttachMovie(GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, int32_t a_depth = -1, const GFxValue* a_initObj = nullptr);
		bool		GotoAndPlay(const char* a_frame);
		bool		GotoAndStop(const char* a_frame);

		//
		void RegisterNumber(const char* a_name, double a_rhs)
		{
			GFxValue s_value(a_rhs);
			m_objectInterface->SetMember(m_value.obj, a_name, &s_value, IsDisplayObject());
		}

		void RegisterBool(const char* a_name, bool a_rhs)
		{
			GFxValue s_value(a_rhs);
			m_objectInterface->SetMember(m_value.obj, a_name, &s_value, IsDisplayObject());
		}

		void RegisterString(const char* a_name, const char* a_rhs)
		{
			GFxValue s_value(a_rhs);
			m_objectInterface->SetMember(m_value.obj, a_name, &s_value, IsDisplayObject());
		}

		GFC_MEMORY_REDEFINE_NEW(GFxValue, 0);
	protected:
		bool	IsManagedValue() const;
		void	AcquireManagedValue(const GFxValue& a_rhs);
		void	ReleaseManagedValue();
		void	ChangeType(uint32_t a_type);

		union ValueUnion
		{
		public:
			constexpr ValueUnion() : obj(nullptr)
			{}
		public:
			double			  number;
			bool			  boolean;
			const char*		  string;
			const char**	  managedString;
			const wchar_t_t*  wideString;
			const wchar_t_t** managedWideString;
			void*			  obj;
		};
		static_assert(sizeof(ValueUnion) == 0x8);
	public:
		ObjectInterface*		m_objectInterface;
		uint32_t 				m_type;
		uint32_t				pad0C;
		ValueUnion				m_value;
	};
	static_assert(sizeof(GFxValue) == 0x18);
}
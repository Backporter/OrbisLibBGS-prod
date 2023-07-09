#include "GFxValue.h"

namespace ConsoleRE
{
	// GFxValue::DisplayInfo
	GFxValue::DisplayInfo::DisplayInfo(double a_x, double a_y) : _x(a_x), _y(a_y)
	{
	}

	GFxValue::DisplayInfo::DisplayInfo(double a_rot) : _rotation(a_rot)
	{
	}

	GFxValue::DisplayInfo::DisplayInfo(bool a_visable) : _visible(a_visable)
	{
	}

	void			 GFxValue::DisplayInfo::Clear() 
	{
		_flags = 0; 
	}
	
	double			 GFxValue::DisplayInfo::GetAlpha() const 
	{
		return _alpha; 
	}

	double			 GFxValue::DisplayInfo::GetFOV() const
	{ 
		return _fov; 
	}

	double			 GFxValue::DisplayInfo::GetRotation() const 
	{ 
		return _rotation; 
	}

	bool			 GFxValue::DisplayInfo::GetVisible() const 
	{ 
		return _visible; 
	}
	
	const GMatrix3D* GFxValue::DisplayInfo::GetPerspectiveMatrix3D() const 
	{ 
		return IsFlagSet(4096) ? &_perspMatrix3D : nullptr; 
	}

	const GMatrix3D* GFxValue::DisplayInfo::GetViewMatrix3D() const 
	{ 
		return IsFlagSet(8192) ? &_viewMatrix3D : nullptr; 
	}

	double			 GFxValue::DisplayInfo::GetX() const 
	{
		return _x; 
	}
	
	double			 GFxValue::DisplayInfo::GetY() const 
	{ 
		return _y; 
	}

	double			 GFxValue::DisplayInfo::GetZ() const
	{ 
		return _z; 
	}

	double			 GFxValue::DisplayInfo::GetXRotation() const 
	{ 
		return _xRotation; 
	}

	double			 GFxValue::DisplayInfo::GetYRotation() const 
	{ 
		return _yRotation; 
	}

	double			 GFxValue::DisplayInfo::GetXScale() const 
	{ 
		return _xScale; 
	}

	double			 GFxValue::DisplayInfo::GetYScale() const 
	{ 
		return _yScale; 
	}

	double			 GFxValue::DisplayInfo::GetZScale() const 
	{ 
		return _zScale; 
	}

	bool			 GFxValue::DisplayInfo::IsFlagSet(uint32_t a_flag) const
	{
		return  (_flags & a_flag) == a_flag;
	}

	void             GFxValue::DisplayInfo::Initialize(uint32_t a_varsSet, double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale, double a_fov, const GMatrix3D* a_viewM, const GMatrix3D* a_perspM)
	{
		// assert(a_viewM);
		// assert(a_perspM);

		_flags = a_varsSet;
		_x = a_x;
		_y = a_y;
		_rotation = a_rotation;
		_xScale = a_xScale;
		_yScale = a_yScale;
		_alpha = a_alpha;
		_visible = a_visible;
		_z = a_z;
		_xRotation = a_xRotation;
		_yRotation = a_yRotation;
		_zScale = a_zScale;
		_fov = a_fov;
		_viewMatrix3D = *a_viewM;
		_perspMatrix3D = *a_perspM;
	}

	void             GFxValue::DisplayInfo::SetVisible(bool a_visible)
	{
		_flags |= 64;
		_visible = a_visible;
	}

	void             GFxValue::DisplayInfo::SetPerspectiveMatrix3D(const GMatrix3D* a_mat)
	{
		if (a_mat)
		{
			_flags |= 4096;
			_perspMatrix3D = *a_mat;
		}
		else
		{
			ClearFlags(4096);
		}
	}

	void             GFxValue::DisplayInfo::Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible)
	{
		_flags |= (1 | 2 | 4 | 8 | 16 | 32 | 64);
		_x = a_x;
		_y = a_y;
		_rotation = a_rotation;
		_xScale = a_xScale;
		_yScale = a_yScale;
		_alpha = a_alpha;
		_visible = a_visible;
	}

	void             GFxValue::DisplayInfo::Set(double a_x, double a_y, double a_rotation, double a_xScale, double a_yScale, double a_alpha, bool a_visible, double a_z, double a_xRotation, double a_yRotation, double a_zScale)
	{
		_flags |= (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024);
		_x = a_x;
		_y = a_y;
		_rotation = a_rotation;
		_xScale = a_xScale;
		_yScale = a_yScale;
		_alpha = a_alpha;
		_visible = a_visible;
		_z = a_z;
		_xRotation = a_xRotation;
		_yRotation = a_yRotation;
		_zScale = a_zScale;
	}

	void             GFxValue::DisplayInfo::SetViewMatrix3D(const GMatrix3D* a_mat)
	{
		if (a_mat)
		{
			_flags |= 8192;
			_viewMatrix3D = *a_mat;
		}
		else
		{
			ClearFlags(8192);
		}
	}

	void             GFxValue::DisplayInfo::SetAlpha(double a_alpha)
	{
		_flags |= 32;
		_alpha = a_alpha;
	}

	void             GFxValue::DisplayInfo::SetFOV(double a_fov)
	{
		_flags |= 2048;
		_fov = a_fov;
	}

	void             GFxValue::DisplayInfo::SetPosition(double a_x, double a_y)
	{
		_flags |= (1 | 2);
		_x = a_x;
		_y = a_y;
	}

	void             GFxValue::DisplayInfo::SetRotation(double a_degrees)
	{
		_flags |= (4);
		_rotation = a_degrees;
	}

	void             GFxValue::DisplayInfo::SetScale(double a_xScale, double a_yScale)
	{
		_flags |= (8 | 16);
		_xScale = a_xScale;
		_yScale = a_yScale;
	}

	void             GFxValue::DisplayInfo::SetX(double a_x)
	{
		_flags |= (1);
		_x = a_x;
	}

	void             GFxValue::DisplayInfo::SetXRotation(double a_degrees)
	{
		_flags |= (256);
		_xRotation = a_degrees;
	}

	void             GFxValue::DisplayInfo::SetXScale(double a_xScale)
	{
		_flags |= (8);
		_xScale = a_xScale;
	}

	void             GFxValue::DisplayInfo::SetY(double a_y)
	{
		_flags |= (2);
		_y = a_y;
	}

	void             GFxValue::DisplayInfo::SetYRotation(double a_degrees)
	{
		_flags |= (4);
		_yRotation = a_degrees;
	}

	void             GFxValue::DisplayInfo::SetYScale(double a_yScale)
	{
		_flags |= (16);
		_yScale = a_yScale;
	}

	void             GFxValue::DisplayInfo::SetZ(double a_z)
	{
		_flags |= (128);
		_z = a_z;
	}

	void             GFxValue::DisplayInfo::SetZScale(double a_zScale)
	{
		_flags |= (1024);
		_zScale = a_zScale;
	}

	void			 GFxValue::DisplayInfo::SetFlags(uint16_t a_flags)
	{
		_flags |= a_flags;
	}

	void			 GFxValue::DisplayInfo::ClearFlags(uint16_t a_flags)
	{
		_flags &= ~(a_flags);
	}
	
	// GFxValue::ObjectInterface
	GFxValue::ObjectInterface::ObjectInterface(GFxMovieRoot* a_movieRoot) :
		m_movieRoot(a_movieRoot)
	{}

	void		GFxValue::ObjectInterface::ObjectAddRef(GFxValue* a_value, void* a_obj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::ObjectAddRef);
		Relocation<func_t> func("", 0x11DF130);
		return func(this, a_value, a_obj);
	}

	void		GFxValue::ObjectInterface::ObjectRelease(GFxValue* a_value, void* a_obj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::ObjectRelease);
		Relocation<func_t> func("", 0x11DFFC0);
		return func(this, a_value, a_obj);
	}

	bool		GFxValue::ObjectInterface::HasMember(void* a_data, const char* a_name, bool a_isDisplayObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::HasMember);
		Relocation<func_t> func("", 0x11E0080);
		return func(this, a_data, a_name, a_isDisplayObj);
	}

	bool		GFxValue::ObjectInterface::GetMember(void* a_data, const char* a_name, GFxValue* a_value, bool a_isDisplayObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::GetMember);
		Relocation<func_t> func("", 0x11E0190);
		return func(this, a_data, a_name, a_value, a_isDisplayObj);
	}

	bool		GFxValue::ObjectInterface::SetMember(void* a_data, const char* a_name, GFxValue* a_value, bool a_isDisplayObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::SetMember);
		Relocation<func_t> func("", 0x11E0370);
		return func(this, a_data, a_name, a_value, a_isDisplayObj);
	}

	bool		GFxValue::ObjectInterface::Invoke(void* a_data, GFxValue* a_result, const char* a_name, GFxValue* a_args, uint32_t a_numArgs, bool a_isDisplayObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::Invoke);
		Relocation<func_t> func("", 0x11E0480);
		return func(this, a_data, a_result, a_name, a_args, a_numArgs, a_isDisplayObj);
	}

	bool		GFxValue::ObjectInterface::DeleteMember(void* a_data, const char* a_name, bool a_isDisplayObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::DeleteMember);
		Relocation<func_t> func("", 0x11E08B0);
		return func(this, a_data, a_name, a_isDisplayObj);
	}

	uint32_t	GFxValue::ObjectInterface::GetArraySize(void* a_data)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::GetArraySize);
		Relocation<func_t> func("", 0x11E0A60);
		return func(this, a_data);
	}

	bool		GFxValue::ObjectInterface::SetArraySize(void* a_data, uint32_t a_size)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::SetArraySize);
		Relocation<func_t> func("", 0x11E0A70);
		return func(this, a_data, a_size);
	}

	bool		GFxValue::ObjectInterface::GetElement(void* a_data, uint32_t a_idx, GFxValue* a_value)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::GetElement);
		Relocation<func_t> func("", 0x11E0A90);
		return func(this, a_data, a_idx, a_value);
	}

	bool		GFxValue::ObjectInterface::SetElement(void* a_data, uint32_t a_idx, const GFxValue& a_val)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::SetElement);
		Relocation<func_t> func("", 0x11E0B20);
		return func(this, a_data, a_idx, a_val);
	}

	bool		GFxValue::ObjectInterface::PushBack(void* a_data, const GFxValue& a_value)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::PushBack);
		Relocation<func_t> func("", 0x11E0CE0);
		return func(this, a_data, a_value);
	}

	bool		GFxValue::ObjectInterface::RemoveElements(void* a_data, uint32_t a_idx, int32_t a_count)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::RemoveElements);
		Relocation<func_t> func("", 0x11E0E00);
		return func(this, a_data, a_idx, a_count);
	}

	bool		GFxValue::ObjectInterface::GetDisplayInfo(void* a_data, DisplayInfo* a_displayInfo)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::GetDisplayInfo);
		Relocation<func_t> func("", 0x11E1290);
		return func(this, a_data, a_displayInfo);
	}

	bool		GFxValue::ObjectInterface::SetDisplayInfo(void* a_data, const DisplayInfo& a_displayInfo)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::SetDisplayInfo);
		Relocation<func_t> func("", 0x11E1740);
		return func(this, a_data, a_displayInfo);
	}

	bool		GFxValue::ObjectInterface::SetText(void* a_data, const char* a_text, bool a_isHTML)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::SetText);
		Relocation<func_t> func("", 0x11E2080);
		return func(this, a_data, a_text, a_isHTML);
	}

	bool		GFxValue::ObjectInterface::AttachMovie(void* a_data, GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, int32_t a_depth, const GFxValue* a_initObj)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::AttachMovie);
		Relocation<func_t> func("", 0x11E2760);
		return func(this, a_data, a_movieClip, a_symbolName, a_instanceName, a_depth, a_initObj);
	}

	bool		GFxValue::ObjectInterface::GotoAndPlay(void* a_data, const char* a_frame, bool a_stop)
	{
		using func_t = decltype(&GFxValue::ObjectInterface::GotoAndPlay);
		Relocation<func_t> func("", 0x11E2330);
		return func(this, a_data, a_frame, a_stop);
	}

	bool		GFxValue::ObjectInterface::IsSameContext(const ObjectInterface* a_rhs) const
	{
		return m_movieRoot == a_rhs->m_movieRoot;
	}

	// GFxValue::GFxValue
	GFxValue::GFxValue() : 
		m_objectInterface(nullptr), 
		m_type(std::underlying_type_t<ValueType>(ValueType::kUndefined)),
		pad0C(0), 
		m_value()
	{}

	GFxValue::GFxValue(ValueType a_type) :
		m_objectInterface(nullptr), 
		m_type(std::underlying_type_t<ValueType>(a_type)),
		pad0C()
	{
		// assert(m_type != std::underlying_type_t<ValueType>(ValueType::kObject) && m_type != std::underlying_type_t<ValueType>(ValueType::kArray) && m_type != std::underlying_type_t<ValueType>(ValueType::kDisplayObject));
		m_value.string = nullptr;
	}

	GFxValue::GFxValue(double a_rhs) : 
		m_objectInterface(nullptr), 
		m_type(std::underlying_type_t<ValueType>(ValueType::kNumber)),
		pad0C(), 
		m_value()
	{
		m_value.number = a_rhs;
	}

	GFxValue::GFxValue(bool a_rhs) :
		m_objectInterface(nullptr),
		m_type(std::underlying_type_t<ValueType>(ValueType::kBoolean)),
		pad0C(),
		m_value()
	{
		m_value.boolean = a_rhs;
	}

	GFxValue::GFxValue(const char* a_rhs) :
		m_objectInterface(nullptr),
		m_type(std::underlying_type_t<ValueType>(ValueType::kString)),
		pad0C(),
		m_value()
	{
		m_value.string = a_rhs;
	}

	GFxValue::GFxValue(const wchar_t_t* a_rhs) :
		m_objectInterface(nullptr),
		m_type(std::underlying_type_t<ValueType>(ValueType::kStringW)),
		pad0C(),
		m_value()
	{
		m_value.wideString = a_rhs;
	}

	GFxValue::GFxValue(const GFxValue& a_rhs) :
		m_objectInterface(nullptr),
		m_type(a_rhs.m_type),
		pad0C(),
		m_value()
	{
		m_value = a_rhs.m_value;
		
		if (a_rhs.IsManagedValue())
		{
			AcquireManagedValue(a_rhs);
		}
	}

	GFxValue::~GFxValue()
	{
		if (IsManagedValue())
		{
			ReleaseManagedValue();
		}
	}

	GFxValue& GFxValue::operator=(std::nullptr_t)
	{
		SetNull();
		return *this;
	}

	GFxValue& GFxValue::operator=(double a_rhs)
	{
		SetNumber(a_rhs);
		return *this;
	}

	GFxValue& GFxValue::operator=(bool a_rhs)
	{
		SetBoolean(a_rhs);
		return *this;
	}

	GFxValue& GFxValue::operator=(const char* a_rhs)
	{
		SetString(a_rhs);
		return *this;
	}

	GFxValue& GFxValue::operator=(const wchar_t_t* a_rhs)
	{
		SetStringW(a_rhs);
		return *this;
	}

	GFxValue& GFxValue::operator=(const GFxValue& a_rhs)
	{
		if (this != std::addressof(a_rhs)) 
		{
			if (IsManagedValue()) 
			{
				ReleaseManagedValue();
			}

			m_type = a_rhs.m_type;
			m_value = a_rhs.m_value;

			if (a_rhs.IsManagedValue()) 
			{
				AcquireManagedValue(a_rhs);
			}
		}
		return *this;
	}

	GFxValue& GFxValue::operator=(GFxValue&& a_rhs)
	{
		if (this != std::addressof(a_rhs)) 
		{
			m_objectInterface = std::move(a_rhs.m_objectInterface);
			a_rhs.m_objectInterface = nullptr;

			m_type = std::move(a_rhs.m_type);
			a_rhs.m_type = std::underlying_type_t<ValueType>(ValueType::kUndefined);

			m_value.obj = std::move(a_rhs.m_value.obj);
			a_rhs.m_value.obj = nullptr;
		}
		return *this;
	}

	bool GFxValue::operator==(const GFxValue& a_rhs) const
	{
		if (m_type != a_rhs.m_type)
		{
			return false;
		}
		else 
		{
			switch ((m_type & std::underlying_type_t<ValueType>(ValueType::kValueMask)))
			{
			case std::underlying_type_t<ValueType>(ValueType::kBoolean):
				return m_value.boolean == a_rhs.m_value.boolean;
			case std::underlying_type_t<ValueType>(ValueType::kNumber):
				return m_value.number == a_rhs.m_value.number;
			case std::underlying_type_t<ValueType>(ValueType::kString):
				return std::strcmp(GetString(), a_rhs.GetString()) == 0;
			case std::underlying_type_t<ValueType>(ValueType::kStringW):
				return std::wcscoll((const wchar_t*)GetStringW(), (const wchar_t*)a_rhs.GetStringW()) == 0;
			default:
				return m_value.obj == a_rhs.m_value.obj;
			}
		}
	}

	GString GFxValue::ToString() const
	{
		return { GetString() };
	}

	GFxValue::ValueType GFxValue::GetType() const
	{
		return static_cast<GFxValue::ValueType>((m_type & std::underlying_type_t<ValueType>(ValueType::kTypeMask)));
	}

	bool GFxValue::IsUndefined() const
	{
		return GetType() == ValueType::kUndefined;
	}

	bool GFxValue::IsNull() const
	{
		return GetType() == ValueType::kNull;
	}

	bool GFxValue::IsBool() const
	{
		return GetType() == ValueType::kBoolean;
	}

	bool GFxValue::IsNumber() const
	{
		return GetType() == ValueType::kNumber;
	}

	bool GFxValue::IsString() const
	{
		return GetType() == ValueType::kString;
	}

	bool GFxValue::IsStringW() const
	{
		return GetType() == ValueType::kStringW;
	}

	bool GFxValue::IsObject() const
	{
		switch (GetType()) 
		{
		case ValueType::kObject:
		case ValueType::kArray:
		case ValueType::kDisplayObject:
			return true;
		default:
			return false;
		}
	}

	bool GFxValue::IsArray() const
	{
		return GetType() == ValueType::kArray;
	}

	bool GFxValue::IsDisplayObject() const
	{
		return GetType() == ValueType::kDisplayObject;
	}

	bool GFxValue::GetBool() const
	{
		// assert(IsBool());
		return m_value.boolean;
	}

	double GFxValue::GetNumber() const
	{
		// assert(IsNumber());
		return m_value.number;
	}

	std::ptrdiff_t GFxValue::GetSInt() const
	{
		return static_cast<std::ptrdiff_t>(round(GetNumber()));
	}

	std::size_t GFxValue::GetUInt() const
	{
		return static_cast<std::size_t>(round(GetNumber()));
	}

	const char* GFxValue::GetString() const
	{
		// assert(IsString());
		return IsManagedValue() ? *m_value.managedString : m_value.string;
	}

	const wchar_t_t* GFxValue::GetStringW() const
	{
		// assert(IsStringW());
		return IsManagedValue() ? *m_value.managedWideString : m_value.wideString;
	}

	void GFxValue::SetUndefined()
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kUndefined));
	}

	void GFxValue::SetNull()
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kNull));
	}

	void GFxValue::SetBoolean(bool a_val)
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kBoolean));
		m_value.boolean = a_val;
	}

	void GFxValue::SetNumber(double a_val)
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kNumber));
		m_value.number = a_val;
	}

	void GFxValue::SetString(const char* a_str)
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kString));
		m_value.string = a_str;
	}

	void GFxValue::SetStringW(const wchar_t_t* a_str)
	{
		ChangeType(std::underlying_type_t<ValueType>(ValueType::kStringW));
		m_value.wideString = a_str;
	}

	bool GFxValue::HasMember(const char* a_name) const
	{
		// assert(IsObject());
		return m_objectInterface->HasMember(m_value.obj, a_name, IsDisplayObject());
	}

	bool GFxValue::GetMember(const char* a_name, GFxValue* a_value) const
	{
		// assert(IsObject());
		return m_objectInterface->GetMember(m_value.obj, a_name, a_value, IsDisplayObject());
	}

	bool GFxValue::SetMember(const char* a_name, GFxValue* a_value)
	{
		// assert(IsObject());
		return m_objectInterface->SetMember(m_value.obj, a_name, a_value, IsDisplayObject());
	}

	bool GFxValue::Invoke(const char* a_name, GFxValue* a_result, GFxValue* a_args, uint32_t a_numArgs)
	{
		// assert(IsObject());
		return m_objectInterface->Invoke(m_value.obj, a_result, a_name, a_args, a_numArgs, IsDisplayObject());
	}

	bool GFxValue::Invoke(const char* a_name, GFxValue* a_result)
	{
		return Invoke(a_name, a_result, nullptr, 0);
	}

	bool GFxValue::DeleteMember(const char* a_name)
	{
		// assert(IsObject());
		return m_objectInterface->DeleteMember(m_value.obj, a_name, IsDisplayObject());
	}

	uint32_t GFxValue::GetArraySize() const
	{
		// assert(IsObject());
		return m_objectInterface->GetArraySize(m_value.obj);
	}

	bool GFxValue::SetArraySize(uint32_t a_size)
	{
		// assert(IsArray());
		return m_objectInterface->SetArraySize(m_value.obj, a_size);
	}

	bool GFxValue::GetElement(uint32_t a_idx, GFxValue* a_val) const
	{
		// assert(IsArray());
		return m_objectInterface->GetElement(m_value.obj, a_idx, a_val);
	}

	bool GFxValue::SetElement(uint32_t a_idx, const GFxValue& a_val)
	{
		// assert(IsArray());
		return m_objectInterface->SetElement(m_value.obj, a_idx, a_val);
	}

	bool GFxValue::PushBack(const GFxValue& a_value)
	{
		// assert(IsObject());
		return m_objectInterface->PushBack(m_value.obj, a_value);
	}

	bool GFxValue::RemoveElements(uint32_t a_idx, int32_t a_count)
	{
		// assert(IsArray());
		return m_objectInterface->RemoveElements(m_value.obj, a_idx, a_count);
	}

	bool GFxValue::RemoveElement(uint32_t a_idx)
	{
		return RemoveElements(a_idx, 1);
	}

	bool GFxValue::ClearElements()
	{
		return RemoveElements(0);
	}

	bool GFxValue::GetDisplayInfo(DisplayInfo* a_displayInfo) const
	{
		// assert(IsDisplayObject());
		return m_objectInterface->GetDisplayInfo(m_value.obj, a_displayInfo);
	}

	bool GFxValue::SetDisplayInfo(const DisplayInfo& a_displayInfo)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->SetDisplayInfo(m_value.obj, a_displayInfo);
	}

	bool GFxValue::SetText(const char* a_text)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->SetText(m_value.obj, a_text, false);
	}

	bool GFxValue::SetTextHTML(const char* a_html)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->SetText(m_value.obj, a_html, true);
	}

	bool GFxValue::AttachMovie(GFxValue* a_movieClip, const char* a_symbolName, const char* a_instanceName, int32_t a_depth, const GFxValue* a_initObj)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->AttachMovie(m_value.obj, a_movieClip, a_symbolName, a_instanceName, a_depth, a_initObj);
	}

	bool GFxValue::GotoAndPlay(const char* a_frame)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->GotoAndPlay(m_value.obj, a_frame, false);
	}

	bool GFxValue::GotoAndStop(const char* a_frame)
	{
		// assert(IsDisplayObject());
		return m_objectInterface->GotoAndPlay(m_value.obj, a_frame, true);
	}

	bool GFxValue::IsManagedValue() const
	{
		return (m_type & std::underlying_type_t<ValueType>(ValueType::kManagedBit)) == std::underlying_type_t<ValueType>(ValueType::kManagedBit);
	}

	void GFxValue::AcquireManagedValue(const GFxValue& a_rhs)
	{
		// assert(a_rhs.m_value.obj && a_rhs.m_objectInterface);
		m_objectInterface = a_rhs.m_objectInterface;
		m_objectInterface->ObjectAddRef(this, m_value.obj);
	}

	void GFxValue::ReleaseManagedValue()
	{
		// assert(m_value.obj && m_objectInterface);
		m_objectInterface->ObjectRelease(this, m_value.obj);
		m_objectInterface = nullptr;
	}

	void GFxValue::ChangeType(uint32_t a_type)
	{
		if (IsManagedValue())
		{
			ReleaseManagedValue();
		}

		m_type = a_type;
	}
}
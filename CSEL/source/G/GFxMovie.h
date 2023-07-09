#pragma once

#include "../../../OrbisUtil/include/Types.h"

#include "../G/GRefCountBase.h"

namespace ConsoleRE
{
	class GFxFunctionHandler;
	class GFxMovieDef;
	class GFxValue;

	class GFxMovie : public GRefCountBase<GFxMovie, 326>
	{
	public:
		enum PlayState
		{
			Playing = 0,
			Stopped = 1
		};

		enum SetVarType
		{
			SV_Normal = 0,
			SV_Sticky = 1,
			SV_Permanent = 2
		};

		enum SetArrayType
		{
			SA_Int = 0,
			SA_Double = 1,
			SA_Float = 2,
			SA_String = 3,
			SA_StringW = 4,
			SA_Value = 5
		};
	public:
		virtual GFxMovieDef*  GetMovieDef() = 0;
		virtual uint32_t	  GetCurrentFrame() = 0;
		virtual bool		  HasLooped() = 0;
		virtual void		  GotoFrame(uint32_t a_framenum) = 0;
		virtual bool		  GotoLabeledFrame(const char* a_label, int32_t a_offset) = 0;
		virtual void		  SetPlayState(PlayState a_state) = 0;
		virtual PlayState	  GetPlayState() = 0;
		virtual void          SetVisible(bool a_visible) = 0;
		virtual bool          GetVisible() = 0;
		virtual bool          IsAvailable(const char* a_pathToVar) = 0;
		virtual void          CreateString(GFxValue* a_value, const char* a_string) = 0;
		virtual void          CreateStringW(GFxValue* a_value, const wchar_t_t* a_string) = 0;
		virtual void          CreateObject(GFxValue* a_value, const char* a_className = 0, const GFxValue* a_args = 0, uint32_t a_numArgs = 0) = 0;
		virtual void          CreateArray(GFxValue* a_value) = 0;
		virtual void          CreateFunction(GFxValue* a_value, GFxFunctionHandler* a_fc, void* a_userData = 0) = 0;
		virtual bool          SetVariable(const char* a_pathToVar, GFxValue& a_value, SetVarType a_setType = SetVarType::SV_Sticky) = 0;
		virtual bool          GetVariable(GFxValue* a_val, const char* a_pathToVar) = 0;
		virtual bool          SetVariableArray(SetArrayType a_type, const char* a_pathToVar, uint32_t a_index, const void* a_data, uint32_t a_count, SetVarType a_setType = SetVarType::SV_Sticky) = 0;
		virtual bool          SetVariableArraySize(const char* a_pathToVar, uint32_t a_count, SetVarType a_setType = SetVarType::SV_Sticky) = 0;
		virtual uint32_t      GetVariableArraySize(const char* a_pathToVar) = 0;
		virtual bool          GetVariableArray(SetArrayType a_type, const char* a_pathToVar, uint32_t a_index, void* a_data, uint32_t a_count) = 0;
		virtual bool          Invoke(const char* a_methodName, GFxValue* a_result, const GFxValue* a_args, uint32_t a_numArgs) = 0;
		virtual bool          InvokeFmt(const char* a_methodName, GFxValue* a_result, const char* a_argFmt, ...) = 0;
		virtual bool          InvokeArgs(const char* a_methodName, GFxValue* a_result, const char* a_argFmt, va_list a_args) = 0;
	};
}
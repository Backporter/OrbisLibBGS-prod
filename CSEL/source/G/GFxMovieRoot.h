#pragma once

// wchar_t_t
#include "../../../OrbisUtil/include/Types.h"

#include "../G/GFxMovieView.h"

#include <stdint.h>

namespace ConsoleRE
{
	class GFxValue;
	class GFxFunctionHandler;

	// 0x2BA0
	class GFxMovieRoot : public GFxMovieView
	{
	public:
		~GFxMovieRoot() override;
		
		GFxMovieDef*				GetMovieDef() override;
		uint32_t					GetCurrentFrame() override;
		bool						HasLooped() override;
		void						GotoFrame(uint32_t) override;
		bool						GotoLabeledFrame(const char*, int32_t) override;
		void						SetPlayState(PlayState) override;
		PlayState					GetPlayState() override;
		void						SetVisible(bool) override;
		bool						GetVisible() override;
		bool						IsAvailable(const char*) override;
		void						CreateString(GFxValue*, const char*) override;
		void						CreateStringW(GFxValue*, const wchar_t_t*) override;
		void						CreateObject(GFxValue* a_value, const char* a_className = 0, const GFxValue* a_args = 0, uint32_t a_numArgs = 0);
		void						CreateArray(GFxValue* value) override;
		void						CreateFunction(GFxValue*, GFxFunctionHandler*, void* a_userData  = NULL) override;
		bool						SetVariable(const char*, GFxValue&, SetVarType = SetVarType::SV_Sticky) override;
		bool						GetVariable(GFxValue*, const char*) override;
		bool						SetVariableArray(SetArrayType a_type, const char* a_pathToVar, uint32_t a_index, const void* a_data, uint32_t a_count, SetVarType a_setType = SetVarType::SV_Sticky) override;
		bool						SetVariableArraySize(const char* a_pathToVar, uint32_t a_count, SetVarType a_setType = SetVarType::SV_Sticky) override;
		uint32_t					GetVariableArraySize(const char* a_pathToVar) override;
		bool						GetVariableArray(SetArrayType a_type, const char* a_pathToVar, uint32_t a_index, void* a_data, uint32_t a_count) override;
		bool						Invoke(const char * name, GFxValue* result, const GFxValue* args, uint32_t numArgs) override;
		bool						InvokeFmt(const char * name, GFxValue * result, const char * fmt, ...) override;
		bool						InvokeArgs(const char* a_methodName, GFxValue* a_result, const char* a_argFmt, va_list a_args) override;
		void						SetViewport(const GViewport&) override;
		void						GetViewport(GViewport*) override;
		void						SetViewScaleMode(ScaleModeType) override;
		ScaleModeType				GetViewScaleMode() override;
		void						SetViewAlignment(AlignType) override;
		AlignType					GetViewAlignment() override;
		GRectF						GetVisibleFrameRect() override;
		void						SetPerspective3D(GMatrix3D&) override;
		void						SetView3D(GMatrix3D&) override;
		GRectF						GetSafeRect() override;
		void						SetSafeRect(GRectF&) override;
		void						Restart() override;
		float						Advance(float, uint32_t = 2) override;
		void						Display() override;
		void						DisplayPrePass() override;
		void						SetPause(bool) override;
		bool						IsPaused() override;
		void						SetBackgroundColor(GColor) override;
		void						SetBackgroundAlpha(float) override;
		float						GetBackgroundAlpha() override;
		HE_ReturnValueType			HandleEvent(GFxEvent&) override;
		void						GetMouseState(uint32_t a_mouseIndex, float* a_x, float* a_y, uint32_t* a_buttons) override;
		void						NotifyMouseState(float a_x, float a_y, uint32_t a_buttons, uint32_t a_mouseIndex = 0) override;
		bool						HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::HitTest_Shapes, uint32_t a_controllerIdx = 0) override;
		bool						HitTest3D(GPoint3F* a_ptOut, float a_x, float a_y, uint32_t a_controllerIdx = 0) override;
		void						SetExternalInterfaceRetVal(GFxValue&) override;
		void*						GetUserData() override;
		void						SetUserData(void*) override;
		bool						AttachDisplayCallback(char* a_pathToObject, void(*a_callback)(void* a_user), void* a_user) override;
		bool						IsMovieFocused() override;
		bool						GetDirtyFlag(bool = true) override;
		void						SetMouseCursorCount(uint32_t) override;
		uint32_t					GetMouseCursorCount() override;
		void						SetControllerCount(uint32_t) override;
		uint32_t					GetControllerCount() override;
		void						GetStats(GStatBag*, bool = true) override;
		GMemoryHeap*				GetHeap() override;
		void						ForceCollectGarbage() override;
		GPointF						TranslateToScreen(GPointF& a_p, void* a_userMatrix) override;
		GRectF						TranslateToScreen(GRectF& a_p, void* a_userMatrix) override;
		bool						TranslateLocalToScreen(char* a_pathToCharacter,  GPointF& a_pt, GPointF* a_presPt, void* a_userMatrix) override;
		bool                        SetControllerFocusGroup(uint32_t a_controllerIdx, uint32_t a_focusGroupIndex) override;
		uint32_t					GetControllerFocusGroup(uint32_t a_controllerIdx) override;                           
		GFxMovieDef::MemoryContext* GetMemoryContext() override;                                                               
		void                        Release() override;                                                                              
	public:
		void GetVisibleFrameRect_vtbl(GRectF* a_dst)
		{
			Relocation<void(*)(GRectF*, GFxMovieRoot*)> GetVisibleFrameRect("GFxMovieRoot:GetVisibleFrameRect", 0x1188B80);
			GetVisibleFrameRect(a_dst, this);
		}
	public:
	};
}
#pragma once

#include "../G/GFxMovie.h"
#include "../G/GFxMovieDef.h"
#include "../G/GFxStateBag.h"
#include "../G/GPoint.h"
#include "../G/GRect.h"
#include "../G/GViewport.h"

namespace ConsoleRE
{
	class GColor;
	class GFxEvent;
	class GFxValue;
	class GMatrix3D;
	class GMemoryHeap;
	class GPoint3F;
	class GViewport;
	struct GStatBag;

	class GFxMovieView : public GFxMovie, public GFxStateBag
	{
	public:
		enum class ScaleModeType
		{
			SM_NoScale  = 0,
			SM_ShowAll  = 1,
			SM_ExactFit = 2,
			SM_NoBorder = 3
		};

		enum class AlignType
		{
			Align_Center = 0,
			Align_TopCenter = 1,
			Align_BottomCenter = 2,
			Align_CenterLeft = 3,
			Align_CenterRight = 4,
			Align_TopLeft = 5,
			Align_TopRight = 6,
			Align_BottomLeft = 7,
			Align_BottomRight = 8,
			Align_MAX = 9
		};
		
		enum HE_ReturnValueType
		{
			HE_NotHandled = 0,
			HE_Handled = 1,
			HE_NoDefaultAction = 2,
			HE_Completed = 3
		};

		enum HitTestType
		{
			HitTest_Bounds = 0,
			HitTest_Shapes = 1,
			HitTest_ButtonEvents = 2,
			HitTest_ShapesNoInvisible = 3
		};
	public:
		~GFxMovieView() override;
		
		// add
		virtual void                                      SetViewport(const GViewport& a_viewDesc);
		virtual void                                      GetViewport(GViewport* a_viewDesc);                                                                           
		virtual void                                      SetViewScaleMode(ScaleModeType a_type);                                                                             
		virtual ScaleModeType							  GetViewScaleMode();                                                                                           
		virtual void                                      SetViewAlignment(AlignType a_type);
		virtual AlignType								  GetViewAlignment();
		virtual GRectF									  GetVisibleFrameRect();                                                                                        
		virtual void                                      SetPerspective3D(GMatrix3D& a_projMatIn);                                                                     
		virtual void                                      SetView3D(GMatrix3D& a_viewMatIn);                                                                            
		virtual GRectF									  GetSafeRect();                                                                                                
		virtual void                                      SetSafeRect(GRectF& a_rect);                                                                                  
		virtual void                                      Restart();                                                                                                          
		virtual float                                     Advance(float a_deltaT, uint32_t a_frameCatchUpCount = 2);                                                     
		virtual void                                      Display();                                                                                                          
		virtual void                                      DisplayPrePass();                                                                                                   
		virtual void                                      SetPause(bool a_pause);                                                                                             
		virtual bool									  IsPaused();                                                                                                   
		virtual void                                      SetBackgroundColor(GColor a_bgColor);                                                                         
		virtual void                                      SetBackgroundAlpha(float a_alpha);                                                                                  
		virtual float									  GetBackgroundAlpha();                                                                                         
		virtual HE_ReturnValueType                        HandleEvent(GFxEvent& a_event);
		virtual void                                      GetMouseState(uint32_t a_mouseIndex, float* a_x, float* a_y, uint32_t* a_buttons);                        
		virtual void                                      NotifyMouseState(float a_x, float a_y, uint32_t a_buttons, uint32_t a_mouseIndex = 0);                    
		virtual bool                                      HitTest(float a_x, float a_y, HitTestType a_testCond = HitTestType::HitTest_Shapes, uint32_t a_controllerIdx = 0);    
		virtual bool                                      HitTest3D(GPoint3F* a_ptOut, float a_x, float a_y, uint32_t a_controllerIdx = 0);                              
		virtual void                                      SetExternalInterfaceRetVal(GFxValue& a_val);                                                                  
		virtual void*									  GetUserData();                                                                                                
		virtual void                                      SetUserData(void* a_data);                                                                                          
		virtual bool                                      AttachDisplayCallback(char* a_pathToObject, void(*a_callback)(void* a_user), void* a_user);                   
		virtual bool									  IsMovieFocused();                                                                                             
		virtual bool                                      GetDirtyFlag(bool a_doReset = true);                                                                                
		virtual void                                      SetMouseCursorCount(uint32_t a_count);                                                                         
		virtual uint32_t								  GetMouseCursorCount();                                                                                        
		virtual void                                      SetControllerCount(uint32_t a_count);                                                                          
		virtual uint32_t								  GetControllerCount();                                                                                         
		virtual void                                      GetStats(GStatBag* a_bag, bool a_reset = true);                                                                     
		virtual GMemoryHeap*							  GetHeap();                                                                                                    
		virtual void                                      ForceCollectGarbage();                                                                                              
		virtual GPointF                                   TranslateToScreen(GPointF& a_p, void* a_userMatrix);                                                          
		virtual GRectF                                    TranslateToScreen(GRectF& a_p, void* a_userMatrix);                                                           
		virtual bool                                      TranslateLocalToScreen(char* a_pathToCharacter, GPointF& a_pt, GPointF* a_presPt, void* a_userMatrix);  
		virtual bool                                      SetControllerFocusGroup(uint32_t a_controllerIdx, uint32_t a_focusGroupIndex);                            
		virtual uint32_t								  GetControllerFocusGroup(uint32_t a_controllerIdx);                                                       
		virtual GFxMovieDef::MemoryContext*				  GetMemoryContext();                                                                                           
		virtual void                                      Release();                                                                                                          

		void SetViewport(int32_t a_bufW, int32_t a_bufH, int32_t a_left, int32_t a_top, int32_t a_width, int32_t a_height, GViewport::Flag a_flags = GViewport::Flag::kNone)
		{
			SetViewport({ a_bufW, a_bufH, a_left, a_top, a_width, a_height, a_flags });
		}
		
		void InvokeNoReturn(char* a_methodName, GFxValue* a_args, uint32_t a_numArgs)
		{
			using func_t = void(GFxMovieView* const, char*, GFxValue*, uint32_t);
			Relocation<func_t*> func("", 0x118CD70);
			return func(this, a_methodName, a_args, a_numArgs);
		}
	public:
	};
	static_assert(sizeof(GFxMovieView) == 0x18);
}
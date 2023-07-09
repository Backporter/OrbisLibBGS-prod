#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../F/FxDelegate.h"
#include "../G/GFxLoader.h"
#include "../I/IMenu.h"
#include "../S/Setting.h"

#include "../S/State.h"

#include <stdint.h>
#include <functional>

namespace ConsoleRE
{
	class GFxMovieDef;

	class BSScaleformManager
	{
	public:
		static BSScaleformManager* GetSingleton(void)
		{
			Relocation<BSScaleformManager**> Singleton("BSScaleformManager:Singleton", 0x313B278);
			return *Singleton;
		}

		bool LoadMovieEx(IMenu* a_menu, const char* a_fileName, std::function<void(GFxMovieDef*)> a_callback)
		{
			return LoadMovieEx(a_menu, a_fileName, 1, 0.0F, a_callback);
		}

		bool LoadMovieEx(IMenu* a_menu, const char* a_fileName, uint32_t a_mode, std::function<void(GFxMovieDef*)> a_callback)
		{
			return LoadMovieEx(a_menu, a_fileName, a_mode, 0.0F, a_callback);
		}

		bool LoadMovieEx(IMenu* a_menu, const char* a_fileName, uint32_t a_mode, float a_backGroundAlpha, std::function<void(GFxMovieDef*)> a_callback)
		{
			// stack vars
			GViewport viewPort;
			GRectF	  visibleRect;
			GRectF    safeRect;
			float     safeZoneX;
			float     safeZoneY;
			int32_t   width;
			int32_t   height;

			const auto filepath = BuildFilePath(a_fileName);
			if (filepath == "")
			{
				return false;
			}

			const auto def = loader->CreateMovie(filepath.c_str(), 130, 0);
			if (!def)
			{
				return false;
			}

			a_callback(def);

			auto& view = a_menu->uiMovie;
			view.reset(def->CreateInstance());
			if (!view)
			{
				delete def;
				return false;
			}

			view->Release();

			view->SetViewScaleMode((GFxMovieView::ScaleModeType)a_mode);
			view->SetBackgroundAlpha(a_backGroundAlpha);
			CollectDisplayInfo(safeZoneX, safeZoneY, width, height);

			visibleRect = view->GetVisibleFrameRect();

			safeRect.left = safeZoneX;
			safeRect.top = safeZoneY;
			safeRect.right = static_cast<float>((visibleRect.right - visibleRect.left) - safeZoneX);
			safeRect.bottom = static_cast<float>((visibleRect.bottom - visibleRect.top) - safeZoneY);

			view->SetSafeRect(safeRect);

			viewPort.bufferWidth = width;
			viewPort.bufferHeight = height;
			viewPort.width = width;
			viewPort.height = height;

			view->SetViewport(viewPort);
			view->Advance(0.0f);

			if (view->IsAvailable("_root.InitExtensions"))
			{
				view->Invoke("_root.InitExtensions", nullptr, nullptr, 0);
			}

			a_menu->RefreshPlatform();
			return true;
		}

		bool LoadMovieEx_impl(IMenu* a_menu, GPtr<GFxMovieView>& a_viewOut, const char* a_fileName, int a_mode = (int)GFxMovieView::ScaleModeType::SM_ShowAll, float a_backGroundAlpha = 0.0f)
		{
			// stack vars
			GViewport viewPort;
			GRectF	  visibleRect;
			GRectF    safeRect;
			float     safeZoneX;
			float     safeZoneY;
			int32_t   width;
			int32_t   height;

			const auto filepath = BuildFilePath(a_fileName);
			if (filepath == "")
			{
				return false;
			}

			const auto def = loader->CreateMovie(filepath.c_str(), GFxLoader::LoadConstants::kLoadKeepBindData | GFxLoader::LoadConstants::kLoadWaitFrame1);
			if (!def)
			{
				return false;
			}

			auto& view = a_menu->uiMovie;
			view.reset(def->CreateInstance());
			if (!view)
			{
				delete def;
				return false;
			}

			view->Release();

			view->SetViewScaleMode((GFxMovieView::ScaleModeType)a_mode);
			view->SetBackgroundAlpha(a_backGroundAlpha);
			CollectDisplayInfo(safeZoneX, safeZoneY, width, height);
			visibleRect = view->GetVisibleFrameRect();
			safeRect.left = safeZoneX;
			safeRect.top = safeZoneY;
			safeRect.right = static_cast<float>((visibleRect.right - visibleRect.left) - safeZoneX);
			safeRect.bottom = static_cast<float>((visibleRect.bottom - visibleRect.top) - safeZoneY);
			view->SetSafeRect(safeRect);
			viewPort.bufferWidth = width;
			viewPort.bufferHeight = height;
			viewPort.width = width;
			viewPort.height = height;
			view->SetViewport(viewPort);
			
			a_menu->fxDelegate = make_gptr<FxDelegate>();
			a_menu->fxDelegate->RegisterHandler(a_menu);
			a_viewOut->SetState(GFxState::StateType::State_ExternalInterface, a_menu->fxDelegate.get());
			view->Advance(0.0f);

			if (view->IsAvailable("_root.InitExtensions"))
			{
				view->Invoke("_root.InitExtensions", nullptr, nullptr, 0);
			}

			a_menu->RefreshPlatform();
			return true;
		}

		bool LoadSFW(IMenu* a_menu, GPtr<GFxMovieView>& a_viewOut, const char* a_fileName, int a_mode = (int)GFxMovieView::ScaleModeType::SM_ShowAll, float a_backGroundAlpha = 0.0f)
		{
			using func_t = bool(GFxLoader*, IMenu*, GPtr<GFxMovieView>&, const char*, int, float);
			Relocation<func_t*> func("", 0x1117050);
			return func(loader, a_menu, a_viewOut, a_fileName, a_mode, a_backGroundAlpha);
		}
	protected:
		static void	CollectDisplayInfo(float& a_safeZoneX, float& a_safeZoneY, int32_t& a_width, int32_t& a_height)
			{
				const auto* state = BSGraphics::State::GetSingleton();
				if (state)
				{
					const auto aspectRatio = static_cast<double>(state->screenWidth) / static_cast<double>(state->screenHeight);
					if (aspectRatio > 4.0 / 3.0)
					{
						Relocation<const Setting*> fSafeZoneXWide("fSafeZoneXWide", 0x37E98A0);
						Relocation<const Setting*> fSafeZoneYWide("fSafeZoneYWide", 0x37E98B8);

						a_safeZoneX = fSafeZoneXWide->GetFloat();
						a_safeZoneY = fSafeZoneYWide->GetFloat();
					}
					else
					{
						Relocation<Setting*> fSafeZoneX("fSafeZoneX", 0x37E9870);
						Relocation<Setting*> fSafeZoneY("fSafeZoneY", 0x37E9888);

						a_safeZoneX = fSafeZoneX->GetFloat();
						a_safeZoneY = fSafeZoneY->GetFloat();
					}

					a_width = state->frameBufferViewport[0];
					a_height = state->frameBufferViewport[1];

					return;
				}

				a_safeZoneX = 0;
				a_safeZoneY = 0;
				a_width = 0;
				a_height = 0;
			}

		static std::string BuildFilePath(const char* a_filename)
			{
				std::string ret;

				char buffer[MAX_PATH / 2]{ 0 };
				sprintf(buffer, "Interface/%s.swf", a_filename);

				if (!FileExists(buffer))
				{
					memset(buffer, 0, sizeof(buffer));
					sprintf(buffer, "Interface/Exported/%s.gfx", a_filename);

					if (!FileExists(buffer))
					{
						ret = "";
						return ret;
					}
				}

				ret = buffer;
				return ret;
			}

		static bool	FileExists(const char* a_path)
			{
				using func_t = bool(*)(const char*);
				Relocation<func_t> func("GFxLoader::Exists", 0x1111710);
				return func(a_path);
			}
	public:
		GFxLoader*	loader;
	};
}
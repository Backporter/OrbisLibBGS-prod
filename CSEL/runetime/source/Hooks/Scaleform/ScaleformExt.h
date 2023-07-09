#pragma once

#include "../../../Internal/Interfaces/ScaleformInterface/ScaleformInterface.h"

#include "../../../../source/G/GFxMovieRoot.h"
#include "../../../../source/G/GFxFunctionHandler.h"

#include "ext\ScaleFormALL.h"

#include <map>

namespace Scaleform
{
	bool RegisterScaleformCallback(const char* a_plugin, Interface::ScaleformInterface::CallBack_t* a_pluginInfo);

	void RegisterNewScaleform(ConsoleRE::GFxMovieRoot* a_this, uint32_t unk);
}
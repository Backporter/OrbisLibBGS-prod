#pragma once

// Interface::QueryInterface
#include "../Interfaces/QueryInterface/QueryInterface.h"

// PluginInfo
#include "PluginInfo.h"

using PluginQueryLoad_t = bool(Interface::QueryInterface*, PluginInfo*);
using PluginLoad_t = bool(Interface::QueryInterface*);
using PluginRevert_t = bool();
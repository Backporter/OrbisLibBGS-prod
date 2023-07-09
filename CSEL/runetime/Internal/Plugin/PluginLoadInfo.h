#pragma once

#include "PluginAPI.h"

#include <cstdio>
#include <stdint.h>

class PluginLoadInfo
{
public:
	PluginLoadInfo() = default;
	~PluginLoadInfo() = default;
	
	// Get
	inline int64_t				GetPluginHandle() { return m_Pluginhandle; }
	inline PluginInfo*			GetPluginInfo() { return &m_Plugininfo; }
	inline PluginQueryLoad_t*	GetPluginQueryFunc() { return m_PluginQueryFunc; }
	inline PluginLoad_t*		GetPluginLoadFunc() { return m_PluginLoadFunc; }
	inline PluginRevert_t*		GetPluginRevertFunc() { return m_PluginReverFunc; }

	// Set
	inline void SetPluginHandle(int64_t a_Pluginhandle) { m_Pluginhandle = a_Pluginhandle; }
	inline void SetPluginInfo(PluginInfo& a_pluginInfo) { m_Plugininfo = a_pluginInfo; }
	inline void SetPluginQueryFunc(PluginQueryLoad_t* a_PluginQueryFunc) { m_PluginQueryFunc = a_PluginQueryFunc; }
	inline void SetPluginLoadFunc(PluginLoad_t* a_PluginLoadFunc) { m_PluginLoadFunc = a_PluginLoadFunc; }
	inline void SetPluginReverFunc(PluginRevert_t* a_PluginReverFunc) { m_PluginReverFunc = a_PluginReverFunc; }
protected:
	int64_t						m_Pluginhandle{ -1 };
	PluginInfo					m_Plugininfo;
	PluginQueryLoad_t*			m_PluginQueryFunc{ 0 };
	PluginLoad_t*				m_PluginLoadFunc{ 0 };
	PluginRevert_t*				m_PluginReverFunc{ 0 };
};
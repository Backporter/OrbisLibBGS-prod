#pragma once

#include "../Interfaces\QueryInterface\QueryInterface.h"

#if __ORBIS__
#include <stdint.h>
#elif __OPENORBIS__
#include <stdint.h>
#endif

class PluginInfo
{
public:
	static constexpr size_t Version = 1;
public:
	PluginInfo() = default;
	~PluginInfo() = default;

	// Get
	inline size_t		GetPluginInfoVersion() { return m_InterfaceVersion; }
	inline const char*	GetPluginName() { return m_pluginName; }
	inline size_t		GetPluginVersion() { return m_pluginVersion; }
	
	// Set
	inline void 		SetPluginInfoVersion(size_t a_InterfaceVersion) { m_InterfaceVersion = a_InterfaceVersion; }
	inline void 		SetPluginName(const char* a_pluginName) { m_pluginName = a_pluginName; }
	inline void 		SetPluginVersion(size_t a_pluginVersion) { m_pluginVersion = a_pluginVersion; }
protected:
	size_t			m_InterfaceVersion;
	const char*		m_pluginName;
	size_t			m_pluginVersion;
};
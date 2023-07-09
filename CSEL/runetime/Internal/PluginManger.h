#pragma once

#include "../../../OrbisUtil/include/Macro.h"
#include "../../../OrbisUtil/include/FileSystem.h"
#include "../../../OrbisUtil/include/Logger.h"

#include "Plugin\PluginLoadInfo.h"
#include "Plugin/PluginInfo.h"
#include "Plugin/PluginAPI.h"

#include "Interfaces/QueryInterface/QueryInterface.h"
#include "Interfaces/MessagingInterface/MessagingInterface.h"

#include <stdint.h>
#include <assert.h>
#include <mutex>

namespace Internal
{
	class PluginManger
	{
	public:
		struct PluginListener
		{ 
		public:
			PluginListener(size_t a_sender, Interface::MessagingInterface::MessageEventCallback_t a_callback)  : m_sender(a_sender), m_callback(a_callback) { }
		public:
			size_t													m_sender;  
			Interface::MessagingInterface::MessageEventCallback_t*	m_callback; 
		};
	public:
		static constexpr inline const char* PLUGIN_DIR[] = 
		{ 
			// Plugins inside the game package.
			"/app0/data/CSEL/Plugins/", 
			
			// should mira be used, this allows for quick loading of plugins from the USB drive(they need to be a OELF not a ELF!).
			"/_mira/Plugins/", 
			
			// Plugins on the HDD, allows for quick add and removing of plugins.
			"/data/CSEL/Plugins/" };

		using PluginLoadInfoList = std::vector<PluginLoadInfo>;
		using PluginListenerList = std::vector<std::vector<PluginListener>>;
	public:
		PluginManger() { m_Plugins.reserve(10); s_pluginListeners.reserve(10); }
		~PluginManger() = default;

		static PluginManger*	GetSingleton()
		{
			static PluginManger singleton;
			return &singleton;
		}

		int						InitializePlugins();
		int						RemovePlugins();
		PluginInfo*				GetPluginInfoByName(const char* a_name);
		const char*				GetPluginNameFromHandle(size_t a_handle);
		int64_t					GetPluginHandleFromName(const char* a_name);
		size_t					GetLoadedPluginCount();
	public:
		static size_t			QueryPluginHandle();
		static bool				DispatchMessageToListener(size_t a_pluginHandle, size_t a_messageType, void* a_messageData, size_t a_messageLength, const char* a_reciver);
		static bool				RegisterMessageListener(size_t listener, const char* sender, Interface::MessagingInterface::MessageEventCallback_t* handler);
		static bool				UnregisterMessageListener(size_t listener, const char* sender, Interface::MessagingInterface::MessageEventCallback_t* handler);
	protected:
		static size_t						s_currentPluginHandle;
		static PluginLoadInfo*				s_currentPluginInfo;
		static PluginListenerList			s_pluginListeners;
		PluginLoadInfoList					m_Plugins;
	};
}
#include "PluginManger.h"

namespace Internal
{
	// only one we need to create.
	static Interface::QueryInterface g_QueryInterface = { };

	int	PluginManger::InitializePlugins()
	{
		int32_t					s_ret = 0;
		int32_t					s_ret2 = 0;
		int32_t					s_ret3 = 0;
		int32_t					s_handle = 0;
		PluginQueryLoad_t*		s_QueryFunc = 0;
		PluginLoad_t*			s_LoadFunc = 0;
		PluginRevert_t*			m_ReverFunc = 0;
		PluginLoadInfo			s_plugin;

		s_currentPluginInfo = &s_plugin;

		for (const char* plugindir : PLUGIN_DIR)
		{
			auto s_files = xUtilty::FileSystem::GetDirectoryEntries(plugindir, ".prx", true, xUtilty::FileSystem::Full, true);
			for (auto& file : s_files)
			{
				s_currentPluginHandle = m_Plugins.size() + 1;
				s_handle = sceKernelLoadStartModule(file.m_filename.c_str(), 0, 0, 0, 0, 0);
				if (s_handle >= 0)
				{
					s_plugin.SetPluginHandle(s_handle);
					
					s_ret	= sceKernelDlsym(s_handle, "Query",  (void**)&s_QueryFunc);
					s_ret2	= sceKernelDlsym(s_handle, "Load",   (void**)&s_LoadFunc);
					s_ret3	= sceKernelDlsym(s_handle, "Revert", (void**)&m_ReverFunc);

					if (!s_ret && !s_ret2 && !s_ret3)
					{
						s_plugin.SetPluginQueryFunc(s_QueryFunc);
						s_plugin.SetPluginLoadFunc(s_LoadFunc);
						s_plugin.SetPluginReverFunc(m_ReverFunc);

						if (s_QueryFunc(&g_QueryInterface, s_plugin.GetPluginInfo()))
						{
							if (s_LoadFunc(&g_QueryInterface))
							{
								xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kDebug, "\"%s\" Loaded correctly.", file.m_filename.c_str());
								m_Plugins.push_back(s_plugin);
							}
						}
						else
						{
							xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kFatal, "(%s, 0x%lx, %d) Plugin Query Failed... ", file.m_filename.c_str(), s_currentPluginHandle, s_handle);
							assert(0);
						}
					}
					else
					{
						xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning, "(%s 0x%lx %d) Failed to find Query & load exports, aborting plugin initialization.", file.m_filename.c_str(), s_currentPluginHandle, s_handle);
						sceKernelStopUnloadModule(s_handle, 0, 0, 0, 0, 0);
					}
				}
				else
				{
					xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning, "(%s) failed to load for 0x%lx", file.m_filename.c_str(), s_handle);
				}
			}
		}


		s_currentPluginInfo = NULL;
		s_currentPluginHandle = NULL;

		DispatchMessageToListener(0, Interface::MessagingInterface::kPluginsLoaded, NULL, 0, 0);
		DispatchMessageToListener(0, Interface::MessagingInterface::kPluginsLoaded2, NULL, 0, 0);
		return 0;
	}

	int	PluginManger::RemovePlugins()
	{
		for (auto& plugin : m_Plugins)
		{
			auto revertFunc = plugin.GetPluginRevertFunc();
			if (revertFunc)
			{
				revertFunc();
				sceKernelStopUnloadModule(plugin.GetPluginHandle(), 0, 0, 0, 0, 0);
			}
			else
			{
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kFatal, "\"%lx\" failed to revert changes...", plugin.GetPluginHandle());
				assert(false);
			}
		}

		return 0;
	}

	PluginInfo*	PluginManger::GetPluginInfoByName(const char* a_name)
	{
		for (auto& plugins : m_Plugins)
		{
			auto s_pluginInfo = plugins.GetPluginInfo();
			auto s_name = s_pluginInfo->GetPluginName();
			if (s_name && !strcasecmp(a_name, s_name))
			{
				return s_pluginInfo;
			}
		}

		return nullptr;
	}

	const char*	PluginManger::GetPluginNameFromHandle(size_t a_handle)
	{
		if (a_handle == 0)
			return "SELF";

		else if (a_handle > 0 && a_handle <= m_Plugins.size())
			return m_Plugins[a_handle - 1].GetPluginInfo()->GetPluginName();
		else
			return nullptr;
	}

	int64_t	PluginManger::GetPluginHandleFromName(const char* a_name)
	{
		if (!strcasecmp(a_name, "SELF"))
			return 0;

		int index = 1;
		for (auto& plugin : m_Plugins)
		{
			if (!strcasecmp(plugin.GetPluginInfo()->GetPluginName(), a_name))
				return index;

			index++;
		}

		return -1;
	}

	size_t PluginManger::GetLoadedPluginCount()
	{
		size_t count = m_Plugins.size();
		return s_currentPluginInfo ? ++count : count;
	}

	size_t PluginManger::QueryPluginHandle()
	{
		if (!s_currentPluginHandle)
		{
			assert(false);
		}

		return s_currentPluginHandle;
	}

	bool PluginManger::DispatchMessageToListener(size_t a_pluginHandle, size_t a_messageType, void* a_messageData, size_t a_messageLength, const char* a_reciver)
	{
		uint32_t s_called = 0;
		int64_t s_target = -1;

		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kInfo, "Dispatching Message(%d) to plugin Messagers", a_messageType);

		if (!s_pluginListeners.size())
		{
			xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kInfo, "no listeners registered");
			return false;
		}

		else if (a_pluginHandle >= s_pluginListeners.size())
		{
			xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kWarning, "sender is not in the list");
			return false;
		}

		if (a_reciver)
		{
			s_target = GetSingleton()->GetPluginHandleFromName(a_reciver);
			if (s_target == -1)
				return false;
		}

		const char* senderName = GetSingleton()->GetPluginNameFromHandle(a_pluginHandle);
		if (!senderName)
		{
			return false;
		}

		for (auto iter = s_pluginListeners[a_pluginHandle].begin(); iter != s_pluginListeners[a_pluginHandle].end(); ++iter)
		{
			Interface::MessagingInterface::Message msg;
			msg.type = a_messageType;
			msg.sender = senderName;
			msg.dataSize = a_messageLength;
			msg.data = a_messageData;

			if (s_target != -1)
			{
				if (iter->m_sender == s_target)
				{
					iter->m_callback(&msg);
					return true;
				}
			}
			else
			{
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kInfo, "sending message type %u to plugin %u", a_messageType, iter->m_sender);
				iter->m_callback(&msg);
				s_called++;
			}
		}
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kInfo, "dispatched message to %d senders", s_called);
		return s_called ? true : false;
	}

	bool PluginManger::RegisterMessageListener(size_t listener, const char* sender, Interface::MessagingInterface::MessageEventCallback_t* handler)
	{
		uint32_t numPlugins = GetSingleton()->GetLoadedPluginCount() + 1;
		if (s_pluginListeners.size() < numPlugins)
		{
			s_pluginListeners.resize(numPlugins + 5);
		}

		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kInfo, "registering plugin listener for %s at %u of %u", sender, listener, numPlugins);

		if (listener > GetSingleton()->GetLoadedPluginCount() || !handler)
		{
			return false;
		}

		if (sender)
		{
			auto target = GetSingleton()->GetPluginHandleFromName(sender);
			if (target == -1)
			{
				return false;
			}

			for (auto iter = s_pluginListeners[target].begin(); iter != s_pluginListeners[target].end(); ++iter)
			{
				if (iter->m_sender == listener)
				{
					return true;
				}
			}

			PluginListener newListener(listener, handler);
			s_pluginListeners[target].push_back(newListener);
		}
		else
		{
			uint32_t idx = 0;
			for (auto iter = s_pluginListeners.begin(); iter != s_pluginListeners.end(); ++iter)
			{
				if (idx && idx != listener)
				{
					bool skipCurrentList = false;
					for (auto iterEx = iter->begin(); iterEx != iter->end(); ++iterEx)
					{
						if (iterEx->m_sender == listener)
						{
							skipCurrentList = true;
							break;
						}
					}

					if (skipCurrentList)
					{
						continue;
					}

					PluginListener newListener(listener, handler);
					iter->push_back(newListener);
				}

				idx++;
			}
		}

		return true;
	}

	bool PluginManger::UnregisterMessageListener(size_t listener, const char* sender, Interface::MessagingInterface::MessageEventCallback_t* handler)
	{
		return false;
	}

	PluginLoadInfo*					 PluginManger::s_currentPluginInfo = nullptr;
	size_t							 PluginManger::s_currentPluginHandle = 0;
	PluginManger::PluginListenerList PluginManger::s_pluginListeners;
}
#include "MessagingInterface.h"

#include "../../PluginManger.h"

namespace Interface
{
	int MessagingInterface::Message::GetVersion()
	{
		return Version;
	}
	
	int	MessagingInterface::GetInterfaceVersion()																												
	{ 
		return MessagingInterface::Version;
	}
	
	bool MessagingInterface::RegisterPluginCallback(size_t a_pluginHandle, const char* a_sender, MessagingInterface::MessageEventCallback_t* a_callback)			
	{ 
		return Internal::PluginManger::RegisterMessageListener(a_pluginHandle, a_sender, a_callback);										  
	}

	bool MessagingInterface::DispatchLiseners(size_t a_pluginHandle, size_t a_messageType, void* a_messageData, size_t a_messageLength, const char* a_reciver)	
	{ 
		return Internal::PluginManger::DispatchMessageToListener(a_pluginHandle, a_messageType, a_messageData, a_messageLength, a_reciver); 
	}

	bool MessagingInterface::UnegisterPluginCallback(size_t a_pluginHandle, const char* a_sender, MessagingInterface::MessageEventCallback_t* a_callback)
	{ 
		return Internal::PluginManger::UnregisterMessageListener(a_pluginHandle, a_sender, a_callback);
	}
}
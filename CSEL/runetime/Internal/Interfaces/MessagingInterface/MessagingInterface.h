#pragma once

#include "../QueryInterface/QueryInterface.h"

#include <stdio.h>
#include <cstdio>

namespace Interface
{
	class MessagingInterface : public QueryInterface
	{
	public:
		struct Message
		{
		public:
			static constexpr int Version = 1;
		public:
			Message() = default;
			virtual ~Message() = default;

			// add
			virtual int GetVersion();	// { return Version; }
		public:
			const char*	sender;
			int64_t		type;
			void*       data;
			size_t      dataSize;
		};
		static_assert(sizeof(Message) == 0x28);

		enum MessageType : int32_t
		{
			// equal to kNewGame/kMessage_NewGame
			kNewGame,

			// equal to kSaveGame/kMessage_SaveGame
			kSave,

			// equal to kDeleteGame/kMessage_DeleteGame
			kDelete,

			// equal to kPreLoadGame/kMessage_PreLoadGame
			kLoading,

			// equal to kPostLoadGame/kMessage_PostLoadGame
			kLoaded,

			// equal to kInputLoaded/kMessage_InputLoaded
			kInput,

			// equal to kDataLoaded/kMessage_DataLoaded
			kDataLoad,

			// equal to kPostLoad/kMessage_PostLoad
			kPluginsLoaded,

			// equal to kPostPostLoad/kMessage_PostPostLoad
			kPluginsLoaded2,

			// custom, sent right before ConsoleLibInitialize() returns
			kMAIN_LOADED,
		};

		// Directly from SKSE
		enum EventSourceType : int32_t
		{
			kModEvent,
			kCameraEvent,
			kCrosshairEvent,
			kActionEvent,
			kNiNodeUpdateEvent
		};
	public:
		// Interface ID
		static constexpr int TypeID = 4;
		
		// Interface Version
		static constexpr int Version = 1;

		using MessageEventCallback_t = void(Message*);
	public:
		MessagingInterface() = default;
		~MessagingInterface() override = default;

		// override (QueryInterface)
		int	GetInterfaceVersion() override; // { return Version; }
		
		// add
		virtual bool RegisterPluginCallback(size_t a_pluginHandle, const char* a_sender, MessageEventCallback_t* a_callback);
		virtual bool DispatchLiseners(size_t a_pluginHandle, size_t a_messageType, void* a_messageData, size_t a_messageLength, const char* a_reciver);
		virtual bool UnegisterPluginCallback(size_t a_pluginHandle, const char* a_sender, MessageEventCallback_t* a_callback);
	};
	static_assert(sizeof(MessagingInterface) == 0x8);
}
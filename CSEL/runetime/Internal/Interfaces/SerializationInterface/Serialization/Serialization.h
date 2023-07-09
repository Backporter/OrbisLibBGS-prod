#pragma once

#include "../../SerializationInterface/SerializationInterface.h"

#include "../../../../../../OrbisUtil/include/Streams/IMemoryStream.h"
#include "../../../../../../OrbisUtil/include/bitFlags.h"

#include <vector>

namespace Serialization
{
	class SerializationHandler
	{
	public:
		//
		struct SIFF
		{
			struct Header
			{
			public:
				int32_t Magic;
				int32_t Version;
				int32_t ModuleVersion;
				int32_t PluginCount;
			};

			struct RecordTable
			{
			public:
				int32_t RecordType;
				int32_t RecordVersion;
				int32_t RecordSize;
				int32_t RecordOffset;
			};
		};

		//
		struct kFlags
		{
			enum
			{
				kFlagNone  = 0 << 0,
				kFlagRead  = 1 << 1,
				kFlagWrite = 1 << 2,
			};
		};

		//
		using SerializationInterfaceCallbackList = std::vector<Interface::SerializationInterface::Callback>;

		//
		static constexpr uint8_t VaildFlag = 0xFF;

		//
		static constexpr const char* SAVEPATH = "/savedata0/SAVEDATA.DAT.cosave";

		//
		static constexpr uint32_t CaculateDataOffset(uint32_t recordCount)
		{
			uint32_t offset = 0x10;

			for (int i = 0; i < recordCount; i++)
			{
				offset += sizeof(SIFF::RecordTable);
			}

			return offset;
		}
	public:
		SerializationHandler();
		~SerializationHandler() = default;

		//
		static SerializationHandler&					get()
		{
			static SerializationHandler singleton;
			return singleton;
		}

		//
		static xUtilty::BitFlags<uint32_t>&				GetBitFlags()
		{
			static xUtilty::BitFlags<uint32_t> flags;
			return flags;
		}

		//
		static std::vector<Interface::SerializationInterface::Callback>& getCallbacks()
		{
			static std::vector<Interface::SerializationInterface::Callback> callbacks;
			return callbacks;
		}

		//
		static void										RegisterInternal();

		//
		Interface::SerializationInterface::Callback*	GetPluginCallback(size_t a_pluginHandle);
		char*											CreateUUID(size_t a_pluginHandle);
		void											SetPluginRevertFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t*);
		void											SetPluginSaveFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t*);
		void											SetPluginLoadFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t*);
		void											SetPluginFormFunc(size_t a_pluginHandle, Interface::SerializationInterface::formfunc_t*);
		
		// 
		void											SendPluginFormDeletions(uint64_t a_handle);
		void											SendPlguinRevert();
		void											SendPluginLoad();
		void											SendPluginSave();

		// 
		bool											OpenRecord(int32_t a_recordName, int32_t a_recordVersion);
		size_t											ReadRecord(void* a_buffer, size_t a_recrodSize);
		bool											WriteRecrod(int32_t a_recordName, int32_t a_recordVersion);
		bool											OpenWriteRecord(int32_t a_recordName, int32_t a_recordVersion, void* a_recordData, size_t a_recordSize);
		bool											QueryNextRecord(int32_t& a_type, int32_t& a_version, size_t& a_recordSize);
	public:
		Interface::SerializationInterface*	m_serializationInterface { nullptr };
		xUtilty::IMemoryStream*				m_stream { 0 };
	};
}
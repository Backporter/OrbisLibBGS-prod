#include "SerializationInterface.h"

// interal stuff.
#include "Serialization\Serialization.h"

#include "../../../../../OrbisUtil/include/MessageHandler.h"

#if __ORBIS__ 
#include <kernel\uuid.h>
#elif __OPENORBIS__
#include <orbis\libkernel.h>
#endif

#include <assert.h>

namespace Interface
{
	SerializationInterface::Callback::Callback() : m_revertFunc(0), m_saveFunc(0), m_loadFunc(0), m_formFunc(0), m_uuid(0)
	{
		if (!m_uuid)
		{
			m_uuid = reinterpret_cast<char*>(malloc(33));
			if (!m_uuid)
			{
				xUtilty::KernelPrintOut("Failed To allocate Memory for UUID");
			}
			else
			{
				memset(m_uuid, 0, 33);
			}
		}
	}

	SerializationInterface::Callback::~Callback()
	{ 
		if (m_uuid) 
		{ 
			free(m_uuid); 
		}
	}

	int SerializationInterface::Callback::GetVersion()
	{
		return Version;
	}

	char* SerializationInterface::Callback::CreateUUID()
	{
#if __ORBIS__
		if (m_uuid && m_uuid[0] != 0)
			return m_uuid;

		if (m_uuid)
		{
			SceKernelUuid uuid;
			sceKernelUuidCreate(&uuid);

			snprintf(m_uuid, 33, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", (int)uuid.timeLow, (int)uuid.timeMid, (int)uuid.timeHiAndVersion, (int)uuid.clockSeqHiAndReserved, (int)uuid.clockSeqLow, (int)uuid.node[0], (int)uuid.node[1], (int)uuid.node[2], (int)uuid.node[3], (int)uuid.node[4], (int)uuid.node[5]);
			return m_uuid;
		}

		return NULL;

#elif __OPENORBIS__
		if (m_uuid && m_uuid[0] != 0)
			return m_uuid;
		
		if (m_uuid)
		{
			OrbisKernelUuid uuid;
			sceKernelUuidCreate(&uuid);

			snprintf(m_uuid, 33, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", (int)uuid.timeLow, (int)uuid.timeMid, (int)uuid.timeHiAndVersion, (int)uuid.clockSeqHiAndReserved, (int)uuid.clockSeqLow, (int)uuid.node[0], (int)uuid.node[1], (int)uuid.node[2], (int)uuid.node[3], (int)uuid.node[4], (int)uuid.node[5]);
			return m_uuid;
		}

		return NULL;
#else
		return NULL;
#endif
	}

	int	SerializationInterface::GetInterfaceVersion()
	{
		return Version;
	}

	char* SerializationInterface::CreateUUID(size_t a_pluginHandle)											
	{ 
		return Serialization::SerializationHandler::get().GetPluginCallback(a_pluginHandle)->CreateUUID();			 
	}

	void SerializationInterface::SetPluginRevertCallback(size_t a_pluginHandle, callbackFunc_t* a_func)	
	{
		Serialization::SerializationHandler::get().GetPluginCallback(a_pluginHandle)->m_revertFunc = a_func;
	}
	
	void SerializationInterface::SetPluginSaveCallback(size_t a_pluginHandle, callbackFunc_t* a_func)		
	{ 
		Serialization::SerializationHandler::get().GetPluginCallback(a_pluginHandle)->m_saveFunc = a_func;
	}
	
	void SerializationInterface::SetPluginLoadCallback(size_t a_pluginHandle, callbackFunc_t* a_func)		
	{ 
		Serialization::SerializationHandler::get().GetPluginCallback(a_pluginHandle)->m_loadFunc = a_func;
	}
	
	void SerializationInterface::SetPluginFormDeleteCallback(size_t a_pluginHandle, formfunc_t* a_func)	
	{ 
		Serialization::SerializationHandler::get().GetPluginCallback(a_pluginHandle)->m_formFunc = a_func;
	}

	bool SerializationInterface::OpenRecord(int32_t a_recordName, int32_t a_recordVersion)
	{
		return Serialization::SerializationHandler::get().OpenRecord(a_recordName, a_recordVersion);
	}

	size_t SerializationInterface::ReadRecord(void* a_buffer, size_t a_recrodSize)
	{
		return Serialization::SerializationHandler::get().ReadRecord(a_buffer, a_recrodSize);
	}
	
	bool SerializationInterface::WriteRecrod(int32_t a_recordName, int32_t a_recordVersion)
	{
		return Serialization::SerializationHandler::get().WriteRecrod(a_recordName, a_recordVersion);
	}
	
	bool SerializationInterface::OpenWriteRecord(int32_t a_recordName, int32_t a_recordVersion, void* a_recordData, size_t a_recordSize)
	{
		return Serialization::SerializationHandler::get().OpenWriteRecord(a_recordName, a_recordVersion, a_recordData, a_recordSize);
	}
	
	bool SerializationInterface::QueryNextRecord(int32_t& a_type, int32_t& a_version, size_t& a_recordSize)
	{
		return Serialization::SerializationHandler::get().QueryNextRecord(a_type, a_version, a_recordSize);
	}
}
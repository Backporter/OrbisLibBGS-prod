#include "Serialization.h"

#include "../../../../../../OrbisUtil/include/Streams/IFIleStream.h"
#include "../../../../../../OrbisUtil/include/Logger.h"

#include "../../../../../source/T/TESDataHandler.h"

#include "../../../../Version.h"

#include "../../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../../EXTERNAL/SKSE/SKSE.h"
#endif

namespace Serialization
{
	//
	static void SavePluginList(Interface::SerializationInterface* a_info)
	{
		/*
		ConsoleRE::TESDataHandler* handler = ConsoleRE::TESDataHandler::GetSingleton();

		struct IsActiveFunctor
		{
			bool Accept(ConsoleRE::TESFile* modInfo)
			{
				return modInfo && modInfo->IsActive();
			}
		};

		struct LoadedModVisitor
		{
			LoadedModVisitor(std::function<bool(ConsoleRE::TESFile*)> func) :
				modInfoVisitor(func)
			{
			}

			bool Accept(ConsoleRE::TESFile* modInfo)
			{
				return modInfoVisitor(modInfo);
			}

			std::function<bool(ConsoleRE::TESFile*)> modInfoVisitor;
		};

		IsActiveFunctor IsActiveFunctor;
		uint32_t modCount = handler->Unk908.CountIf(IsActiveFunctor);

		a_info->OpenRecord('PLGN', 0);
		a_info->WriteRecordData(&modCount, sizeof(modCount));
		_MESSAGE("Saving plugin list:");

		handler->Unk908.Visit(LoadedModVisitor([&](ConsoleRE::TESFile* modInfo)
		{
			if (modInfo && modInfo->IsActive())
			{
				a_info->WriteRecordData(&modInfo->modIndex, sizeof(modInfo->modIndex));
				if (modInfo->modIndex == 0xFE)
				{
					a_info->WriteRecordData(&modInfo->lightIndex, sizeof(modInfo->lightIndex));
				}

				uint16_t nameLen = strlen(modInfo->fileName);
				a_info->WriteRecordData(&nameLen, sizeof(nameLen));
				a_info->WriteRecordData(modInfo->name, nameLen);

				if (modInfo->modIndex != 0xFE)
				{
					_MESSAGE("\t[%d]\t%s", modInfo->modIndex, &modInfo->name);
				}
				else
				{
					_MESSAGE("\t[FE:%d]\t%s", modInfo->lightIndex, &modInfo->name);
				}
			}
			return true;
		}));
		*/
	}

	//
	static void SerializationRevert(Interface::SerializationInterface*)
	{
#if USE_SKSE_ADDON
		SKSE::MenuOpenCloseRegistrationMapHolder::GetSingleton()->Clear();
		SKSE::InputKeyEventRegistrationMapHolder::GetSingleton()->Clear();
		SKSE::InputControlRegistrationMapHolder::GetSingletion()->Clear();
		SKSE::ModCallbackRegistrationMapHolder::GetSingleton()->Clear();
		SKSE::CrosshairRefEventRegistrationSetHolder::GetSingletion()->Clear();
		SKSE::CameraEventRegistrationSetHolder::GetSingletion()->Clear();
		SKSE::ActionEventRegistrationMapHolder::GetSingletion()->Clear();
		SKSE::NinodeUpdateRegistrationSetHolder::GetSingletion()->Clear();
#endif
	}

	//
	static void SerializationSave(Interface::SerializationInterface* a_info)
	{
#if USE_SKSE_ADDON
#endif
	}

	//
	static void SerializationLoad(Interface::SerializationInterface*)
	{
#if USE_SKSE_ADDON
#endif
	}

	SerializationHandler::SerializationHandler()
	{
		// get the singleton instance.
		m_serializationInterface = Interface::InternalQueryInterfaceFromID<Interface::SerializationInterface>(Interface::SerializationInterface::TypeID);

		// allocate both the memorystream instance and the memory that it needs.
		m_stream = new xUtilty::IMemoryStream(1 * 128 * 128 + 1);
	}

	Interface::SerializationInterface::Callback* SerializationHandler::GetPluginCallback(size_t a_pluginHandle)
	{
		auto& callbacks = getCallbacks();
		if (a_pluginHandle >= callbacks.size())
		{
			callbacks.resize(a_pluginHandle + 1);
		}

		return &callbacks[a_pluginHandle];
	}

	char* SerializationHandler::CreateUUID(size_t a_pluginHandle)
	{
		auto info = GetPluginCallback(a_pluginHandle);
		auto uuid = info->GetUUID();

		// if UUID is not set, set it.
		if (!uuid || uuid[0] == 0)
		{
			info->CreateUUID();
		}

		return uuid;
	}

	void SerializationHandler::SetPluginRevertFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t* a_func)
	{
		auto info = GetPluginCallback(a_pluginHandle);
		info->m_revertFunc = a_func;
	}

	void SerializationHandler::SetPluginSaveFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t* a_func)
	{
		auto info = GetPluginCallback(a_pluginHandle);
		info->m_saveFunc = a_func;
	}

	void SerializationHandler::SetPluginLoadFunc(size_t a_pluginHandle, Interface::SerializationInterface::callbackFunc_t* a_func)
	{
		auto info = GetPluginCallback(a_pluginHandle);
		info->m_loadFunc = a_func;
	}

	void SerializationHandler::SetPluginFormFunc(size_t a_pluginHandle, Interface::SerializationInterface::formfunc_t* a_func)
	{
		auto info = GetPluginCallback(a_pluginHandle);
		info->m_formFunc = a_func;
	}

	void SerializationHandler::RegisterInternal()
	{
		auto& self = get();
		self.CreateUUID(0);

		self.SetPluginRevertFunc(0, SerializationRevert);
		self.SetPluginSaveFunc(0, SerializationSave);
		self.SetPluginLoadFunc(0, SerializationLoad);
	}

	void SerializationHandler::SendPluginFormDeletions(uint64_t a_handle)
	{
		for (auto& callbcks : getCallbacks())
		{
			auto callback = callbcks.GetFormFunc();
			{
				if (callback)
				{
					callback(a_handle);
				}
			}
		}
	}

	void SerializationHandler::SendPlguinRevert()
	{
		for (auto& callbcks : getCallbacks())
		{
			auto callback = callbcks.GetRevertFunc();
			if (callback)
			{
				callback(m_serializationInterface);
			}
		}
	}

	void SerializationHandler::SendPluginSave()
	{
	}

	void SerializationHandler::SendPluginLoad()
	{
	}

	// 
	bool SerializationHandler::OpenRecord(int32_t a_recordName, int32_t a_recordVersion)
	{
		assert(false);
	}

	size_t SerializationHandler::ReadRecord(void* a_buffer, size_t a_recrodSize)
	{
		assert(false);
	}

	bool SerializationHandler::WriteRecrod(int32_t a_recordName, int32_t a_recordVersion)
	{
		assert(false);
	}

	bool SerializationHandler::OpenWriteRecord(int32_t a_recordName, int32_t a_recordVersion, void* a_recordData, size_t a_recordSize)
	{
		assert(false);
	}

	bool SerializationHandler::QueryNextRecord(int32_t& a_type, int32_t& a_version, size_t& a_recordSize)
	{
		assert(false);
	}
}
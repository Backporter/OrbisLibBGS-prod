#pragma once

#include "../QueryInterface/QueryInterface.h"

#include <cstring>

namespace Interface
{
	class SerializationInterface : public QueryInterface
	{
	public:
		// Interface ID
		static constexpr int			TypeID = 6;
		
		// Interface Version
		static constexpr int			Version = 1;

		// 
		using callbackFunc_t = void(SerializationInterface*);

		//
		using formfunc_t = void(uint64_t);

		//
		class Callback
		{
		public:
			static constexpr int Version = 1;
		public:
			Callback();
			virtual ~Callback();

			// add
			virtual int   GetVersion();	// { return Version; }
			virtual char* CreateUUID(); // { ... }

			// Set
			inline void SetRevertFunc(callbackFunc_t* a_func) { m_revertFunc = a_func; }
			inline void SetSaveFunc(callbackFunc_t* a_func) { m_saveFunc = a_func; }
			inline void SetLoadFunc(callbackFunc_t* a_func) { m_loadFunc = a_func; }
			inline void SetFormFunc(formfunc_t* a_func) { m_formFunc = a_func; }

			// Get
			inline char*			GetUUID() { return m_uuid; }
			inline callbackFunc_t*	GetRevertFunc() { return m_revertFunc; }
			inline callbackFunc_t*	GetSaveFunc() { return m_saveFunc; }
			inline callbackFunc_t*	GetLoadFunc() { return m_loadFunc; }
			inline formfunc_t*		GetFormFunc() { return m_formFunc; }

			// Has
			inline bool HasUUID() { return m_uuid != nullptr; }
			inline bool HasReverFunc() { return static_cast<bool>(m_revertFunc); }
			inline bool HasSaveFunc() { return static_cast<bool>(m_saveFunc); }
			inline bool HasLoadFunc() { return static_cast<bool>(m_loadFunc); }
			inline bool HasFormFunc() { return static_cast<bool>(m_formFunc); }
		public:
			callbackFunc_t*								m_revertFunc;
			callbackFunc_t*								m_saveFunc;
			callbackFunc_t*								m_loadFunc;
			formfunc_t*									m_formFunc;
			char*										m_uuid;
		};
		static_assert(sizeof(Callback) == 0x30);
	public:
		SerializationInterface() = default;
		~SerializationInterface() override = default;

		// override (QueryInterface)
		int	GetInterfaceVersion() override;

		// add
		virtual char*  CreateUUID(size_t a_pluginHandle);
		virtual void   SetPluginRevertCallback(size_t a_pluginHandle, callbackFunc_t*);
		virtual void   SetPluginSaveCallback(size_t a_pluginHandle, callbackFunc_t*);
		virtual void   SetPluginLoadCallback(size_t a_pluginHandle, callbackFunc_t*);
		virtual void   SetPluginFormDeleteCallback(size_t a_pluginHandle, formfunc_t*);

		// not finished... do not use!
		virtual bool   OpenRecord(int32_t a_recordName, int32_t a_recordVersion);
		virtual size_t ReadRecord(void* a_buffer, size_t a_recrodSize);
		virtual bool   WriteRecrod(int32_t a_recordName, int32_t a_recordVersion);
		virtual bool   OpenWriteRecord(int32_t a_recordName, int32_t a_recordVersion, void* a_recordData, size_t a_recordSize);
		virtual bool   QueryNextRecord(int32_t& a_type, int32_t& a_version, size_t& a_recordSize);
	};
	static_assert(sizeof(SerializationInterface) == 0x8);
}
#pragma once

#include "../QueryInterface/QueryInterface.h"

namespace Interface
{
	class ScaleformInterface : public QueryInterface
	{
	public:
		// Interface ID
		static constexpr int TypeID = 3;

		// Interface Version
		static constexpr size_t Version = 1;

		using CallBack_t = bool(void*, void*);
		using InventoryCallback_t = void(void*, void*, void*);
		using RegisterCallback_t = bool(const char*, CallBack_t*);
		using RegisterInventoryCallback_t = void(InventoryCallback_t*);

		class ScaleformPluginInfo
		{
		public:
			static constexpr int Version = 1;
		public:
			ScaleformPluginInfo() = default;
			virtual ~ScaleformPluginInfo() = default;

			// add
			virtual int GetVersion();	// { return Version; }
			
										
			// Get
			const char* GetPluginName() const { return m_name; }
			CallBack_t* GetPluginCallback() const { return m_callback; }
			
			// Set
			void SetPluginName(const char* a_name) { m_name = a_name; }
			void SetPluginCalback(CallBack_t* a_callback) { m_callback = a_callback; }
		public:
			const char* m_name;
			CallBack_t*	m_callback;
		};
		static_assert(sizeof(ScaleformPluginInfo) == 0x18);
	public:
		ScaleformInterface() = default;
		~ScaleformInterface() override = default;
		
		// override (QueryInterface)
		virtual int		GetInterfaceVersion() override;
		
		// add
		virtual bool	RegisterScaleformCallback(const char*, CallBack_t*);
		virtual void	RegisterInventoryCallback(InventoryCallback_t*);
	};
	static_assert(sizeof(ScaleformInterface) == 0x8);
}
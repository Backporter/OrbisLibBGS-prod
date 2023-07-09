#include "API.h"

namespace API
{
	template <typename T>
	T* QueryInterface(Interface::QueryInterface* a_infterface, uint32_t a_interfaceID)
	{
		auto ret = static_cast<T*>(a_infterface->QueryInterfaceFromID(a_interfaceID));
		if (ret && ret->GetInterfaceVersion() > T::Version)
		{
			// 
			xUtilty::KernelPrintOut("Interface Version is newer then expected.");
		}

		return ret;
	}

	struct Storage
	{
	public:
		template <typename T>
		ConsoleRE::BSTEventSource<T>* GetEventSource(Interface::MessagingInterface::EventSourceType a_eventSource)
		{
			assert(m_MessagingInterface);
			return static_cast<ConsoleRE::BSTEventSource<T>*>(m_MessagingInterface->QueryEventSource(a_eventSource));
		}
	public:
		static Storage* GetSingleton()
		{
			static Storage singleton;
			return &singleton;
		}
	public:
		// Interfaces.
		Interface::ScaleformInterface*							m_ScaleformInterface{ nullptr };
		Interface::PapyrusInterface*							m_PapyrusInterface{ nullptr };
		Interface::SerializationInterface*						m_SerializationInterface{ nullptr };
		Interface::TaskInterface*								m_TaskInterface{ nullptr };
		Interface::TrampolineInterface*							m_TrampolineInterface{ nullptr };
		Interface::MessagingInterface*							m_MessagingInterface{ nullptr };

		// EventSource's
		ConsoleRE::BSTEventSource<SKSE::ModCallbackEvent>*		m_ModCallbackEventSource{ nullptr };
		ConsoleRE::BSTEventSource<SKSE::CameraEvent>*			m_CameraEventSource{ nullptr };
		ConsoleRE::BSTEventSource<SKSE::CrosshairRefEvent>*		m_CrosshairRefEventSource{ nullptr };
		ConsoleRE::BSTEventSource<SKSE::ActionEvent>*			m_ActionEventSource{ nullptr };
		ConsoleRE::BSTEventSource<SKSE::NiNodeUpdateEvent>*		m_NiNodeUpdateEventSource{ nullptr };
		
		// Other.
		bool													m_initialized{ false };
		size_t													m_pluginHandle{ static_cast<size_t>(-1) };
		xUtilty::Mutex											m_mutex;
		std::vector<std::function<void()>>						m_funcs;
	};

	void initialize(Interface::QueryInterface* a_interface)
	{
		if (!a_interface)
		{
			throw std::runtime_error(std::string("Invaild Interface Passed To ") + std::string(__FUNCTION__) + " At " + std::to_string(__LINE__) + " In " + std::string(__FILE__));
			return;
		}

		Storage* s_storage = Storage::GetSingleton();
		if (!s_storage->m_initialized)
		{
			s_storage->m_pluginHandle = a_interface->QueryHandle();
			s_storage->m_ScaleformInterface = QueryInterface<Interface::ScaleformInterface>(a_interface, Interface::ScaleformInterface::TypeID);
			s_storage->m_PapyrusInterface = QueryInterface<Interface::PapyrusInterface>(a_interface, Interface::PapyrusInterface::TypeID);
			s_storage->m_SerializationInterface = QueryInterface<Interface::SerializationInterface>(a_interface, Interface::SerializationInterface::TypeID);
			s_storage->m_TaskInterface = QueryInterface<Interface::TaskInterface>(a_interface, Interface::TaskInterface::TypeID);
			s_storage->m_TrampolineInterface = QueryInterface<Interface::TrampolineInterface>(a_interface, Interface::TrampolineInterface::TypeID);
			s_storage->m_MessagingInterface = QueryInterface<Interface::MessagingInterface>(a_interface, Interface::MessagingInterface::TypeID);

			if (s_storage->m_MessagingInterface)
			{
				s_storage->m_ModCallbackEventSource = s_storage->GetEventSource<SKSE::ModCallbackEvent>(Interface::MessagingInterface::EventSourceType::kModEvent);
				s_storage->m_CameraEventSource = s_storage->GetEventSource<SKSE::CameraEvent>(Interface::MessagingInterface::EventSourceType::kCameraEvent);
				s_storage->m_CrosshairRefEventSource = s_storage->GetEventSource<SKSE::CrosshairRefEvent>(Interface::MessagingInterface::EventSourceType::kCrosshairEvent);
				s_storage->m_ActionEventSource = s_storage->GetEventSource<SKSE::ActionEvent>(Interface::MessagingInterface::EventSourceType::kActionEvent);
				s_storage->m_NiNodeUpdateEventSource = s_storage->GetEventSource<SKSE::NiNodeUpdateEvent>(Interface::MessagingInterface::EventSourceType::kNiNodeUpdateEvent);
			}

			s_storage->m_initialized = true;
		}
	}

	void RegisterForAPIInitEvent(std::function<void()> a_func)
	{
		{
			auto* storage = Storage::GetSingleton();
			const xUtilty::scoped_lock<xUtilty::Mutex> lock(storage->m_mutex);
			if (!storage->m_initialized)
			{
				storage->m_funcs.push_back(a_func);
				return;
			}
		}

		a_func();
	}


	size_t GetPluginHandle()
	{
		return Storage::GetSingleton()->m_pluginHandle;;
	}

	Interface::ScaleformInterface* GetScaleformInterface()
	{
		return Storage::GetSingleton()->m_ScaleformInterface;
	}

	Interface::PapyrusInterface* GetPapyrusInterface()
	{
		return Storage::GetSingleton()->m_PapyrusInterface;
	}

	Interface::SerializationInterface* GetSerializationInterface()
	{
		return Storage::GetSingleton()->m_SerializationInterface;
	}

	Interface::TaskInterface* GetTaskInterface()
	{
		return Storage::GetSingleton()->m_TaskInterface;
	}

	Interface::TrampolineInterface* GetTrampolineInterface()
	{
		return Storage::GetSingleton()->m_TrampolineInterface;
	}

	Interface::MessagingInterface* GetMessagingInterface()
	{
		return Storage::GetSingleton()->m_MessagingInterface;
	}

	ConsoleRE::BSTEventSource<SKSE::ModCallbackEvent>* GetModCallbackEventSource()
	{
		return Storage::GetSingleton()->m_ModCallbackEventSource;
	}

	ConsoleRE::BSTEventSource<SKSE::CameraEvent>* GetCameraEventSource()
	{
		return Storage::GetSingleton()->m_CameraEventSource;
	}

	ConsoleRE::BSTEventSource<SKSE::CrosshairRefEvent>* GetCrosshairRefEventSource()
	{
		return Storage::GetSingleton()->m_CrosshairRefEventSource;
	}

	ConsoleRE::BSTEventSource<SKSE::ActionEvent>* GetActionEventSource()
	{
		return Storage::GetSingleton()->m_ActionEventSource;
	}

	ConsoleRE::BSTEventSource<SKSE::NiNodeUpdateEvent>* GetNiNodeUpdateEventSource()
	{
		return Storage::GetSingleton()->m_NiNodeUpdateEventSource;
	}

	xUtilty::Trampoline& GetTrampoline()
	{
		static xUtilty::Trampoline trampoline;
		return trampoline;
	}

	void AllocateTrampoline(size_t a_size, bool a_tryRerserve)
	{
		auto&	tampoline = GetTrampoline();
		auto	trampolineInterface = GetTrampolineInterface();
		
		if (trampolineInterface && a_tryRerserve)
		{
			auto memory = trampolineInterface->Allocate(GetPluginHandle(), a_size);
			if (memory)
			{
				tampoline.Setup(memory, 0, a_size);
			}
		}
	}
}
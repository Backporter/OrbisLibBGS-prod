#include "../V/VirtualMachine.h"

#include "../I/IFunction.h"
#include "../S/SkyrimVM.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		namespace Internal
		{
			VirtualMachine* VirtualMachine::GetSingleton()
			{
				auto vm = SkyrimVM::GetSingleton();
				return vm ? static_cast<VirtualMachine*>(vm->impl.get()) : nullptr;
			}

			void VirtualMachine::RegisterFunction(IFunction* fn)
			{
				// Atomic count of the number of papyrus functions binded.
				static volatile int g_fncount = 0;

				// store names
				const char* className = fn->GetObjectTypeName().c_str();
				const char* funcName = fn->GetName().c_str();

				// Log the Class::Name of the function count
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "VirtualMachine::RegisterFunction is registering %s::%s of %u", className, funcName, g_fncount);

				if (BindNativeMethod(fn))
				{
					// inc
					__sync_add_and_fetch(&g_fncount, 1);
				}
				else
				{
					xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kWarning, "Failed to bind %s::%s[%u]", className, funcName, g_fncount);
				}
			}
		}
	}
}
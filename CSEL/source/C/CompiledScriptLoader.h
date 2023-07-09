#pragma once

#include "../B/BSTSmartPointer.h"
#include "../I/ILoader.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class ErrorLogger;
		class IStore;

		class CompiledScriptLoader : public ILoader
		{
		public:
			~CompiledScriptLoader() override;

			// override (ILoader)
			ILoader* Clone() override;
			void     SetScriptStore(const BSTSmartPointer<IStore>& a_store) override;
			bool     GetClass(const char* a_name, BSScript::UnlinkedTypes::Object& a_object) override;
		private:
			ErrorLogger*            errorHandler;
			BSTSmartPointer<IStore>	scriptStore;
			BSTArray<void*>			Unk_28;
			uint64_t				Unk_30;
			uint64_t				Unk_38;
			uint64_t				Unk_48;
			uint64_t				Unk_50;
		};
		static_assert(sizeof(CompiledScriptLoader) == 0x48);
	}
}
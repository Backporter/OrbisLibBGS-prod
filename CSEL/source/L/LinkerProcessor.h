#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTSmartPointer.h"
#include "../I/IObjectProcessor.h"

namespace ConsoleRE
{
	namespace BSScript
	{
		class ErrorLogger;
		class IVirtualMachine;
		class ObjectTypeInfo;

		class LinkerProcessor : public IObjectProcessor
		{
		public:
			~LinkerProcessor() override;

			// override (IObjectProcessor)
			virtual IObjectProcessor*	Clone() override;
			virtual void				SetLoader(ILoader* a_loader) override;
			virtual bool				Process(const BSFixedString&) override;
		private:
			IVirtualMachine*											vm;
			ErrorLogger*												errorHandler;
			ILoader*													loader;
			bool                                                        allowRelinking;
			BSScrapArray<BSFixedString>                                 loadedParents;
			BSScrapArray<BSFixedString>                                 objectsToTypecheck;
			BSScrapArray<BSFixedString>                                 processQueue;
			BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* classMap;
		};
		static_assert(sizeof(LinkerProcessor) == 0x78);
	}
}

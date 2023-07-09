#pragma once

#include "../B/BaseFormComponent.h"
#include <functional>

namespace ConsoleRE
{
	class TESBoundObject;

	struct ContainerObject
	{
		int32_t             count;
		uint32_t            pad04;
		TESBoundObject*     obj;
		void*				itemExtra;
	};

	class TESContainer : public BaseFormComponent
	{
	public:
		~TESContainer() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// finders
		template <typename Op>
		ContainerObject* Find(Op& a_op)
		{
			for (int i = 0; i < numContainerObjects; i++)
			{
				if (containerObjects[i] && a_op.Accept(containerObjects[i]))
					return containerObjects[i];
				else
					return nullptr;
			}

			return nullptr;
		}

		ContainerObject* Find(std::function<bool(ContainerObject*)> a_func)
		{
			for (int i = 0; i < numContainerObjects; i++)
			{
				if (containerObjects[i] && a_func(containerObjects[i]))
					return containerObjects[i];
				else
					return nullptr;
			}
			
			return nullptr;
		}

		// Visitors
		void Visit(std::function<bool(ContainerObject*)> a_func)
		{
			for (int i = 0; i < numContainerObjects; i++)
			{
				if (containerObjects[i] && !a_func(containerObjects[i]))
					break;
			}
		}

		template <typename Op>
		void Visit(Op& a_op)
		{
			for (int i = 0; i < numContainerObjects; i++)
			{
				if (containerObjects[i] && !a_op.Accept(containerObjects[i]))
					break;
			}
		}

		// couters
		template <typename Op>
		uint32_t Count(Op& a_op)
		{
			uint32_t count = 0;
			for (uint32_t n = 0; n < numContainerObjects; n++)
			{
				auto* pEntry = containerObjects[n];
				if (pEntry && a_op.Accept(pEntry))
					count++;

			}
			return count;
		}

		uint32_t Count(std::function<bool(ContainerObject*)> a_func)
		{
			uint32_t count = 0;
			for (uint32_t n = 0; n < numContainerObjects; n++)
			{
				auto* pEntry = containerObjects[n];
				if (pEntry && a_func(pEntry))
					count++;

			}
			return count;
		}
	public:
		ContainerObject** containerObjects;
		uint32_t		  numContainerObjects;
	};
	static_assert(sizeof(TESContainer) == 0x18);
}
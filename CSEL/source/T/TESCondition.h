#pragma once

namespace ConsoleRE
{
	class TESCondition
	{
	public:
		TESCondition() : head(0) 
		{}

		~TESCondition()
		{
			//auto cur = head;
			//while (cur)
			//{
			//	auto next cur->next;
			//	delete cur;
			//	cur = next;
			//}
			//
			//head = nullptr;
		}
	public:
		void* head;
	};
}
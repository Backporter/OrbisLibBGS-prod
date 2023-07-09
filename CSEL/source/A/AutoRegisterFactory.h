#pragma once

namespace ConsoleRE
{
	template <class Parent, class Manager>
	class AutoRegisterFactory : public Parent
	{
	public:
		static_assert(sizeof(AutoRegisterFactory) == 0x8);
		virtual ~AutoRegisterFactory();
	};
}

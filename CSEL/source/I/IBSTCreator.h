#pragma once

namespace ConsoleRE
{
	template <class T>
	struct IBSTCreator
	{
	public:
		virtual ~IBSTCreator(); 

		// add
		virtual T*		CreateImpl() const = 0;
		virtual void	Destroy(const T* a_val) const = 0;
	public:
	};
	static_assert(sizeof(IBSTCreator<void*>) == 0x8);
}

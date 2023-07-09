#pragma once

namespace ConsoleRE
{
	class hkpPhantom;

	class hkpPhantomListener
	{
	public:
		virtual ~hkpPhantomListener();

		// add
		virtual void PhantomAddedCallback(hkpPhantom* a_phantom);
		virtual void PhantomRemovedCallback(hkpPhantom* a_phantom);
		virtual void PhantomShapeSetCallback(hkpPhantom* a_phantom);
		virtual void PhantomDeletedCallback(hkpPhantom* a_phantom);
	};
	static_assert(sizeof(hkpPhantomListener) == 0x8);
}
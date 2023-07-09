#pragma once

namespace ConsoleRE
{
	class hkpEntity;

	class hkpEntityListener
	{
	public:
		virtual ~hkpEntityListener();

		// add
		virtual void EntityAddedCallback(hkpEntity* a_entity);
		virtual void EntityRemovedCallback(hkpEntity* a_entity);
		virtual void EntityShapeSetCallback(hkpEntity* a_entity);
		virtual void EntitySetMotionTypeCallback(hkpEntity* a_entity);
		virtual void EntityDeletedCallback(hkpEntity* a_entity);
	public:
	};
}
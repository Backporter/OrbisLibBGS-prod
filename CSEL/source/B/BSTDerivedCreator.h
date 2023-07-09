#pragma once

#include "../I/IBSTCreator.h"

namespace ConsoleRE
{
	template <class Derived, class Parent>
	struct BSTDerivedCreator : public IBSTCreator<Parent>
	{
	public:
		virtual ~BSTDerivedCreator();

		// override (IBSTCreator<Parent>)
		Parent*		CreateImpl() const override;
		void		Destroy(const Parent* a_val) const override;
	public:
	};
}
#pragma once

#include "../B/bhkShapeCollection.h"

namespace ConsoleRE
{
	class bhkListShape : public bhkShapeCollection
	{
	public:
		~bhkListShape() override;

		// override (bhkShapeCollection)
		const NiRTTI* GetRTTI() const override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
	public:
		uint64_t unk28;
	};
}
#pragma once

#include "../B/BSGeometry.h"

namespace ConsoleRE
{
	class BSTriShape : public BSGeometry
	{
	public:
		~BSTriShape() override;

		// override (BSGeometry)
		const NiRTTI* GetRTTI() const override;
		BSTriShape*   AsTriShape() override;
		NiObject*     CreateClone(NiCloningProcess& a_cloning) override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
	public:
		uint16_t triangleCount;
		uint16_t vertexCount;
	};
	static_assert(sizeof(BSTriShape) == 0x158);
}
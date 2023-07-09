#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	struct NAVMESH_PORTAL
	{
		union Nav
		{
			uint32_t navMeshID;
			NavMesh* navMesh;
		};
		static_assert(sizeof(Nav) == 0x8);
	public:
		Nav      nav;
		uint16_t triIndex;
		uint16_t pad0A;
		uint32_t pad0C;
	};
	static_assert(sizeof(NAVMESH_PORTAL) == 0x10);

	class ExtraNavMeshPortal : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kNavMeshPortal>;
	public:
		~ExtraNavMeshPortal();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NAVMESH_PORTAL portal;
	};
	static_assert(sizeof(ExtraNavMeshPortal) == 0x20);
}
#pragma once

#include "../B/BSIntrusiveRefCounted.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTSmartPointer.h"
#include "../M/MemoryManager.h"
#include "../N/NiPoint3.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BSNavmeshObstacleData;
	class BSNavmeshObstacleUndoData;
	class BSPathingCell;
	class BSPathingDoor;

	struct BSNavmeshVertex
	{
	public:
		NiPoint3 location;
	};
	static_assert(sizeof(BSNavmeshVertex) == 0xC);

	struct BSNavmeshTriangle
	{
	public:
		enum class TriangleFlag
		{
			kNone = 0,
			kEdge0_Link = 1 << 0,
			kEdge1_Link = 1 << 1,
			kEdge2_Link = 1 << 2,
			kDeleted = 1 << 3,
			kNoLargeCreatures = 1 << 4,
			kOverlapping = 1 << 5,
			kPreferred = 1 << 6,
		};

		enum class TraversalFlag
		{
			kNone = 0,
			kEdge0_CoverValueQuarter = 1 << 0,
			kEdge0_CoverValueHalf = 1 << 1,
			kEdge0_CoverValueTri = 1 << 2,
			kEdge0_CoverValueFull = 1 << 3,
			kEdge0_Left = 1 << 4,
			kEdge0_Right = 1 << 5,
			kEdge1_CoverValueQuarter = 1 << 6,
			kEdge1_CoverValueHalf = 1 << 7,
			kEdge1_CoverValueTri = 1 << 8,
			kEdge1_CoverValueFull = 1 << 9,
			kEdge1_Left = 1 << 10,
			kEdge1_Right = 1 << 11
		};
	public:
		uint16_t vertices[3];
		uint16_t triangles[3];
		uint16_t triangleFlags;
		uint16_t traversalFlags;
	};
	static_assert(sizeof(BSNavmeshTriangle) == 0x10);

	struct BSNavmeshTriangleEdgePortal
	{
	public:
		uint32_t otherMeshID;
		uint16_t triangle;
		int8_t	 edgeIndex;
		uint8_t	 pad7;
	};
	static_assert(sizeof(BSNavmeshTriangleEdgePortal) == 0x8);

	struct BSNavmeshEdgeExtraInfo
	{
	public:
		uint32_t					type;
		BSNavmeshTriangleEdgePortal portal;
	};
	static_assert(sizeof(BSNavmeshEdgeExtraInfo) == 0xC);

	struct BSNavmeshTriangleDoorPortal
	{
	public:
		BSTSmartPointer<BSPathingDoor>	door;
		uint16_t						owningTriangleIndex;
		uint16_t						pad0A;
		uint32_t						pad0C;
	};
	static_assert(sizeof(BSNavmeshTriangleDoorPortal) == 0x10);

	struct BSNavmeshClosedDoorInfo
	{
	public:
		BSTSmartPointer<BSPathingDoor>	door;
		uint16_t						triangleIndex;
		uint16_t						pad0A;
		uint32_t						pad0C;
	};
	static_assert(sizeof(BSNavmeshClosedDoorInfo) == 0x10);

	struct BSNavmeshCoverEdge
	{
	public:
		uint16_t vertices[2];
		uint32_t data;
	};
	static_assert(sizeof(BSNavmeshCoverEdge) == 0x8);

	struct BSNavmeshGrid
	{
	public:
		uint32_t							 gridSize;
		float                                columnSectionLen;
		float                                rowSectionLen;
		NiPoint3                             gridBoundsMin;
		NiPoint3                             gridBoundsMax;
		uint32_t							 pad24;
		SimpleArray<BSTArray<uint16_t>>		 gridData;
	};
	static_assert(sizeof(BSNavmeshGrid) == 0x30);

	class BSNavmesh : public BSIntrusiveRefCounted
	{
	public:
		virtual ~BSNavmesh();

		// add
		virtual uint32_t QNavmeshID() = 0;
	public:
		uint32_t														pad00C;
		BSTArray<BSNavmeshVertex>										vertices;
		BSTArray<BSNavmeshTriangle>										triangles;
		BSTArray<BSNavmeshEdgeExtraInfo>								extraEdgeInfo;
		BSTArray<BSNavmeshTriangleDoorPortal>							doorPortals;
		BSTArray<BSNavmeshClosedDoorInfo>								closedDoors;
		BSTArray<BSNavmeshCoverEdge>									coverArray;
		BSNavmeshGrid													meshGrid;
		BSTArray<NiPointer<BSNavmeshObstacleUndoData>>					obstacles;
		BSTHashMap<uint16_t, NiPointer<BSNavmeshObstacleData>>*			triangleToObstacleMap;
		BSTArray<void*>													unk0B8;
		BSTSmartPointer<BSPathingCell>									parentCell;
		void*															unk0D0;
	};
	static_assert(sizeof(BSNavmesh) == 0xD8);
}
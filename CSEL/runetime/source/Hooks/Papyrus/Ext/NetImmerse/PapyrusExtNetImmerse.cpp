#include "../NetImmerse/PapyrusExtNetImmerse.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/B/BipedAnim.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/N/NiAVObject.h"
#include "../../../../../../source/P/PlayerCharacter.h"
#include "../../../../../../source/RTTI.h"
#include "../../../../../../source/B/BSGeometry.h"
#include "../../../../../../source/R/ReferenceArray.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

#include "../../../../Hooks/TaskPool/TaskPool.h"
#include "../../../../../Internal/Tasks/Tasks/TaskUpdateWorldData.h"

namespace PapyrusExtNetImmerse
{
	// I really hate doing this...
	using namespace ConsoleRE;

	NiAVObject* ResolveNode(TESObjectREFR* obj, BSFixedString nodeName, bool firstPerson)
	{
		if (!obj)
			return NULL;

		NiAVObject* ret = obj->Get3D1();

		PlayerCharacter* player = TES_RTTI(obj, TESObjectREFR, PlayerCharacter);
		if (player && player->loadedData)
			ret = firstPerson ? player->Unk820.get()->root : player->loadedData->data3D.get();

		if (obj && nodeName.m_data[0] && ret)
			ret = ret->GetObjectByName(nodeName);

		return ret;

	}

#pragma region
	bool GetNodeWorldPosition(StaticFunctionTag* base, TESObjectREFR* obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
	 	NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
	 	if (object && inArray.size() == 3)
	 	{
	 		inArray[0] = object->world.translate.x;
	 		inArray[1] = object->world.translate.y;
	 		inArray[2] = object->world.translate.z;
	 
	 		return true;
	 	}
	 
	 	return false;
	 }

	bool GetNodeLocalPosition(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 3) 
		{
			inArray[0] = object->local.translate.x;
			inArray[1] = object->local.translate.y;
			inArray[2] = object->local.translate.z;

			return true;
		}
	
		return false;
	}
	
	bool GetRelativeNodePosition(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeNameA, BSFixedString nodeNameB, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* objectA = ResolveNode(obj, nodeNameA, firstPerson);
		NiAVObject* objectB = ResolveNode(obj, nodeNameB, firstPerson);

		if (objectA && objectB && inArray.size() == 3) 
		{
			float x = objectB->world.translate.x - objectA->world.translate.x;
			float y = objectB->world.translate.y - objectA->world.translate.y;
			float z = objectB->world.translate.z - objectA->world.translate.z;
	
			inArray[0] = x;
			inArray[1] = y;
			inArray[2] = z;

			return true;
		}
	
		return false;
	}
	
	bool SetNodeLocalPosition(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, std::vector<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 3) 
		{
			object->local.translate.x = inArray[0];
			object->local.translate.y = inArray[1];
			object->local.translate.z = inArray[2];
	
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
	
			return true;
		}
	
		return false;
	}
	
	bool GetNodeLocalRotationEuler(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 3) 
		{
			float heading, attitude, bank;
	
			object->local.rotate.GetEulerAngles(heading, attitude, bank);
	
			heading		*= 180 / NI_PI;
			attitude	*= 180 / NI_PI;
			bank		*= 180 / NI_PI;
	
			inArray[0] = heading;
			inArray[1] = attitude;
			inArray[2] = bank;
	
			return true;
		}
	
		return false;
	}
	
	bool GetNodeWorldRotationEuler(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 3) 
		{
			float heading, attitude, bank;
			object->local.rotate.GetEulerAngles(heading, attitude, bank);
	
			heading		*= 180 / NI_PI;
			attitude	*= 180 / NI_PI;
			bank		*= 180 / NI_PI;
	
			inArray[0] = heading;
			inArray[1] = attitude;
			inArray[2] = bank;
			return true;
		}
	
		return false;
	}
	
	bool SetNodeLocalRotationEuler(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, std::vector<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 3) 
		{
			float heading, attitude, bank;
	
			heading		= inArray[0];
			attitude	= inArray[1];
			bank		= inArray[2];
	
			heading		*= NI_PI / 180;
			attitude	*= NI_PI / 180;
			bank		*= NI_PI / 180;
	
			object->local.rotate.SetEulerAngles(heading, attitude, bank);
	
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
	
			return true;
		}
	
		return false;
	}
	
	bool SetNodeLocalRotationMatrix(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, std::vector<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 9) 
		{
			object->local.rotate.entry[0][0] = inArray[0];
			object->local.rotate.entry[0][1] = inArray[1];
			object->local.rotate.entry[0][2] = inArray[2];
	
			object->local.rotate.entry[1][0] = inArray[3];
			object->local.rotate.entry[1][1] = inArray[4];
			object->local.rotate.entry[1][2] = inArray[5];
	
			object->local.rotate.entry[2][0] = inArray[6];
			object->local.rotate.entry[2][1] = inArray[7];
			object->local.rotate.entry[2][2] = inArray[8];
	
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
	
			return true;
		}
	
		return false;
	}
	
	bool GetNodeLocalRotationMatrix(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 9)
		{
			inArray[0] = object->local.rotate.entry[0][0];
			inArray[1] = object->local.rotate.entry[0][1];
			inArray[2] = object->local.rotate.entry[0][2];
			inArray[3] = object->local.rotate.entry[1][0];
			inArray[4] = object->local.rotate.entry[1][1];
			inArray[5] = object->local.rotate.entry[1][2];
			inArray[6] = object->local.rotate.entry[2][0];
			inArray[7] = object->local.rotate.entry[2][1];
			inArray[8] = object->local.rotate.entry[2][2];
	
			return true;
		}
	
		return false;
	}
	
	bool GetNodeWorldRotationMatrix(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, reference_array<float> inArray, bool firstPerson)
	{
		NiAVObject* object = ResolveNode(obj, nodeName, firstPerson);
		if (object && inArray.size() == 9)
		{
			inArray[0] = object->world.rotate.entry[0][0];
			inArray[1] = object->world.rotate.entry[0][1];
			inArray[2] = object->world.rotate.entry[0][2];
			inArray[3] = object->world.rotate.entry[1][0];
			inArray[4] = object->world.rotate.entry[1][1];
			inArray[5] = object->world.rotate.entry[1][2];
			inArray[6] = object->world.rotate.entry[2][0];
			inArray[7] = object->world.rotate.entry[2][1];
			inArray[8] = object->world.rotate.entry[2][2];
			return true;
		}

		return false;
	}
#pragma endregion

	bool HasNode(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object != NULL;
	}

	float GetNodeWorldPositionX(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->world.translate.x : 0;
	}

	float GetNodeWorldPositionY(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->world.translate.y : 0;
	}

	float GetNodeWorldPositionZ(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->world.translate.z : 0;
	}

	float GetNodeLocalPositionX(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->local.translate.x : 0;
	}

	float GetNodeLocalPositionY(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->local.translate.y : 0;
	}

	float GetNodeLocalPositionZ(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->local.translate.z : 0;
	}

	float GetRelativeNodePositionX(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeNameA, BSFixedString nodeNameB, bool firstPerson)
	{
		NiAVObject	* objectA = ResolveNode(obj, nodeNameA, firstPerson);
		NiAVObject	* objectB = ResolveNode(obj, nodeNameB, firstPerson);

		return (objectA && objectB) ? objectB->world.translate.x - objectA->world.translate.x : 0;
	}

	float GetRelativeNodePositionY(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeNameA, BSFixedString nodeNameB, bool firstPerson)
	{
		NiAVObject	* objectA = ResolveNode(obj, nodeNameA, firstPerson);
		NiAVObject	* objectB = ResolveNode(obj, nodeNameB, firstPerson);

		return (objectA && objectB) ? objectB->world.translate.y - objectA->world.translate.y : 0;
	}

	float GetRelativeNodePositionZ(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeNameA, BSFixedString nodeNameB, bool firstPerson)
	{
		NiAVObject	* objectA = ResolveNode(obj, nodeNameA, firstPerson);
		NiAVObject	* objectB = ResolveNode(obj, nodeNameB, firstPerson);

		return (objectA && objectB) ? objectB->world.translate.z - objectA->world.translate.z : 0;
	}

	float GetNodeScale(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);

		return object ? object->local.scale : 0;
	}

	void SetNodeLocalPositionX(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, float value, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);
	
		if (object)
		{
			object->local.translate.x = value;
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
		}
	}
	
	void SetNodeLocalPositionY(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, float value, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);
	
		if (object)
		{
			object->local.translate.y = value;
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
		}
	}
	
	void SetNodeLocalPositionZ(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, float value, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);
	
		if (object)
		{
			object->local.translate.z = value;
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
		}
	}
	
	void SetNodeScale(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, float value, bool firstPerson)
	{
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);
	
		if (object)
		{
			object->local.scale = value;
			TaskPool::PushQueue(new Tasks::TaskUpdateWorldData(object));
		}
	}

	void SetNodeTextureSet(StaticFunctionTag* base, TESObjectREFR * obj, BSFixedString nodeName, BGSTextureSet * textureSet, bool firstPerson)
	{
		if (!textureSet) return;
	
		NiAVObject	* object = ResolveNode(obj, nodeName, firstPerson);
	
		if (object)
		{
			BSGeometry * geometry = object->AsGeometry();	
			if (geometry)
			{
				BSTaskPool * taskPool = BSTaskPool::GetSingleton();
				if (taskPool)
				{
					taskPool->SetNiGeometryTexture(geometry, textureSet);
				}
			}
		}
	}

	bool RegisterNetImmerse(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldPosition),			StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeWorldPosition",		"NetImmerse", GetNodeWorldPosition));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalPosition),			StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeLocalPosition",		"NetImmerse", GetNodeLocalPosition));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetRelativeNodePosition),		StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, BSFixedString, reference_array<float>, bool>	("GetRelativeNodePosition",		"NetImmerse", GetRelativeNodePosition));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalPosition),			StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, std::vector<float>, bool>						("SetNodeLocalPosition",		"NetImmerse", SetNodeLocalPosition));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalRotationEuler),		StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeLocalRotationEuler",	"NetImmerse", GetNodeLocalRotationEuler));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalRotationEuler),		StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, std::vector<float>, bool>						("SetNodeLocalRotationEuler",	"NetImmerse", SetNodeLocalRotationEuler));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalRotationMatrix),	StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeLocalRotationMatrix",	"NetImmerse", GetNodeLocalRotationMatrix));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalRotationMatrix),	StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, std::vector<float>, bool>						("SetNodeLocalRotationMatrix",	"NetImmerse", SetNodeLocalRotationMatrix));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldRotationEuler),		StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeWorldRotationEuler",	"NetImmerse", GetNodeWorldRotationEuler));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldRotationMatrix),	StaticFunctionTag, bool, TESObjectREFR*, BSFixedString, reference_array<float>, bool>					("GetNodeWorldRotationMatrix",	"NetImmerse", GetNodeWorldRotationMatrix));
		//

		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(HasNode),						StaticFunctionTag, bool,	TESObjectREFR*, BSFixedString, bool>									("HasNode",                    "NetImmerse", HasNode));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldPositionX),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeWorldPositionX",      "NetImmerse", GetNodeWorldPositionX));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldPositionY),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeWorldPositionY",      "NetImmerse", GetNodeWorldPositionY));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeWorldPositionZ),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeWorldPositionZ",      "NetImmerse", GetNodeWorldPositionZ));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalPositionX),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeLocalPositionX",      "NetImmerse", GetNodeLocalPositionX));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalPositionY),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeLocalPositionY",      "NetImmerse", GetNodeLocalPositionY));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeLocalPositionZ),			StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeLocalPositionZ",      "NetImmerse", GetNodeLocalPositionZ));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNodeScale),					StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, bool>									("GetNodeScale",               "NetImmerse", GetNodeScale));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeScale),					StaticFunctionTag, void,	TESObjectREFR*, BSFixedString, float, bool>								("SetNodeScale",               "NetImmerse", SetNodeScale));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalPositionX),			StaticFunctionTag, void,	TESObjectREFR*, BSFixedString, float, bool>								("SetNodeLocalPositionX",      "NetImmerse", SetNodeLocalPositionX));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalPositionY),			StaticFunctionTag, void,	TESObjectREFR*, BSFixedString, float, bool>								("SetNodeLocalPositionY",      "NetImmerse", SetNodeLocalPositionY));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeLocalPositionZ),			StaticFunctionTag, void,	TESObjectREFR*, BSFixedString, float, bool>								("SetNodeLocalPositionZ",      "NetImmerse", SetNodeLocalPositionZ));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNodeTextureSet),				StaticFunctionTag, void,	TESObjectREFR*, BSFixedString, BGSTextureSet*, bool>					("SetNodeTextureSet",          "NetImmerse", SetNodeTextureSet));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetRelativeNodePositionX),		StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, BSFixedString, bool>						("GetRelativeNodePositionX",   "NetImmerse", GetRelativeNodePositionX));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetRelativeNodePositionY),		StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, BSFixedString, bool>						("GetRelativeNodePositionY",   "NetImmerse", GetRelativeNodePositionY));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetRelativeNodePositionZ),		StaticFunctionTag, float,	TESObjectREFR*, BSFixedString, BSFixedString, bool>						("GetRelativeNodePositionZ",   "NetImmerse", GetRelativeNodePositionZ));
		
		return true;
	}
}
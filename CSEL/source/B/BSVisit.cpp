#include "../B/BSVisit.h"
#include "../N/NiAVObject.h"
#include "../N/NiNode.h"

namespace ConsoleRE
{
	namespace BSVisit
	{
		BSVisitControl TraverseScenegraphGeometries(NiAVObject* a_object, std::function<BSVisitControl(BSGeometry*)> a_func)
		{
			if (!a_object) 
			{
				return BSVisitControl::kContinue;
			}
		
			auto geom = a_object->AsGeometry();
			if (geom) 
			{
				return a_func(geom);
			}
		
			auto result = BSVisitControl::kContinue;
			auto node = a_object->AsNode();
			if (node) 
			{
				for (auto& child : node->children) 
				{
					result = TraverseScenegraphGeometries(child.get(), a_func);
					if (result == BSVisitControl::kStop) 
					{
						break;
					}
				}
			}
		
			return result;
		}
	}
}
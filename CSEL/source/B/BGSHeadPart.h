#pragma once

#include "../B/BSTArray.h"
#include "../B/BGSTextureSet.h"
#include "../B/BGSColorForm.h"
#include "../B/BGSListForm.h"
#include "../B/BSFixedString.h"
#include "../T/TESForm.h"
#include "../T/TESModelTri.h"

namespace ConsoleRE
{
	class BGSHeadPart : 
		public TESForm,
		public TESFullName, 
		public TESModelTextureSwap
	{
	public:
		static constexpr int TypeID = 12;
		BGSHeadPart();
		virtual ~BGSHeadPart();

		bool IsExtraPart() { return (flags & 8) == 8; }
	public:
		uint8_t									 flags;                         
		uint8_t                                  pad069;                        
		uint16_t                                 pad06A;                        
		uint32_t								 type;                          
		BSTArray<BGSHeadPart*>                   extraParts;   
		BGSTextureSet*                           textureSet;                  
		TESModelTri                              morphs[3];
		BGSColorForm*                            color;                       
		BGSListForm*                             validRaces;                  
		BSFixedString                            formEditorID;                
	};
}
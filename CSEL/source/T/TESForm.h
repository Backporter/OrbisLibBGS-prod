#pragma once

#include "../B/BaseFormComponent.h"

#include "../T/TESFullName.h"
#include "../T/TESWeightForm.h"
#include "../T/TESValueForm.h"
#include "../T/TESModel.h"
#include "../T/TESModelTextureSwap.h"
#include "../B/BGSKeywordForm.h"

#include "../RTTI.h"

namespace ConsoleRE
{
	class BGSLoadFormBuffer;
	class BGSSaveFormBuffer;
	class TESBoundObject;
	class TESFile;

	struct FORM;
	struct FORM_GROUP;

	class TESObjectREFR;
	class TESObjectARMO;
	class TESObjectLIGH;
	class BGSBipedObjectForm;
	class AlchemyItem;
	class Actor;

	class TESForm : public BaseFormComponent
	{
	public:
		static constexpr int TypeID = 0;
	public:
		~TESForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
		
		// add
		virtual void					InitializeData(void);
		virtual void					ClearData(void);
		virtual bool					Load(TESFile* a_mod);
		virtual bool					LoadPartial(TESFile* a_mod);
		virtual bool					LoadEdit(TESFile* a_mod);
		virtual TESForm*				CreateDuplicateForm(bool a_createEditorID, void* a_arg2);
		virtual bool					AddChange(uint32_t a_changeFlags);
		virtual void					RemoveChange(uint32_t a_changeFlags);
		virtual bool					FindInFileFast(TESFile* a_mod);
		virtual bool					CheckSaveGame(BGSSaveFormBuffer* a_buf);
		virtual void					SaveGame(BGSSaveFormBuffer* a_buf);
		virtual void					LoadGame(BGSLoadFormBuffer* a_buf);
		virtual void					InitLoadGame(BGSLoadFormBuffer* a_buf);
		virtual void					FinishLoadGame(BGSLoadFormBuffer* a_buf);
		virtual void					Revert(BGSLoadFormBuffer* a_buf);
		virtual void					InitItemImpl();
		virtual TESFile*				GetDescriptionOwnerFile() const;
	    virtual uint8_t					GetSavedFormType() const;
	    virtual void					GetFormDetailedString(char* a_buf, uint32_t a_bufLen);
		virtual bool					GetKnown() const;
		virtual bool					GetRandomAnim() const;
		virtual bool					GetPlayable() const;
		virtual bool					IsHeadingMarker() const;
		virtual bool					GetDangerous() const;
		virtual bool					QHasCurrents() const;
		virtual bool					GetObstacle() const;
		virtual bool					QIsLODLandObject() const;
		virtual bool					GetOnLocalMap() const;
		virtual bool					GetMustUpdate() const;
		virtual void					SetOnLocalMap(bool a_set);
		virtual bool					GetIgnoredBySandbox() const;
		virtual void					SetDelete(bool a_set);
		virtual void					SetAltered(bool a_set);
		virtual void					SaveObjectBound();
		virtual void					LoadObjectBound(TESFile* a_mod);
		virtual bool					IsBoundObject() const;
		virtual bool					IsObject() const;
		virtual bool					IsMagicItem() const;
		virtual bool					IsWater() const;
		virtual TESObjectREFR*			AsReference1();
		virtual const TESObjectREFR*	AsReference2() const;
		virtual uint32_t				GetRefCount() const;
		virtual const char*				GetTextForParsedSubTag(const BSFixedString& a_tag) const;
		virtual void					Copy(TESForm* a_srcForm);
		virtual bool					BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly);
		virtual void					CreateGroupData(FORM* a_form, FORM_GROUP* a_group);
		virtual const char*				GetFormEditorID() const;
		virtual bool					SetFormEditorID(const char* a_str);
		virtual bool					IsParentForm();
		virtual bool					IsParentFormTree();
		virtual bool					IsFormTypeChild(uint32_t a_type);
		virtual bool					Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount);
	    virtual void					SetFormID(uint32_t a_id, bool a_updateFile);
		virtual const char*				GetObjectTypeName() const;
		virtual bool					QAvailableInGame() const;

		TESFullName*		 Cast2FullForm()			{  return TES_RTTI(this, TESForm, TESFullName);		    }
		TESWeightForm*		 Cast2WeightForm()			{  return TES_RTTI(this, TESForm, TESWeightForm);	    }
		TESValueForm*		 Cast2ValueForm()			{  return TES_RTTI(this, TESForm, TESValueForm);	    }
		AlchemyItem*		 Cast2AlchemyItem()			{  return TES_RTTI(this, TESForm, AlchemyItem);		    }
		BGSKeywordForm*		 Cast2KeywordForm()			{  return TES_RTTI(this, TESForm, BGSKeywordForm);	    }
		TESModel*			 Cast2ModelForm()			{  return TES_RTTI(this, TESForm, TESModel);		    }
		TESModelTextureSwap* Cast2TextureSwapForm()		{  return TES_RTTI(this, TESForm, TESModelTextureSwap); }
		Actor*				 Cast2ActorForm()			{  return TES_RTTI(this, TESForm, Actor);				}

		static TESForm*		 GetFormFromID(uint32_t ID)
		{
			typedef TESForm*(*_FN)(uint32_t);
			Relocation<_FN> FN("", 0xE24A0);
			return FN(ID);
		}

		TESObjectREFR*		 AsReference() { return AsReference1(); }
		const TESObjectREFR* AsReference() const { return AsReference2(); }

		bool IsAmmo()			const noexcept { return FormType == 0x2A;      }
		bool IsArmor()			const noexcept { return FormType == 0x1A;      }
		bool IsBook()			const noexcept { return FormType == 0x1B;      }
		bool IsKey()			const noexcept { return FormType == 0x2D;      }
		bool IsSoulGem() 		const noexcept { return FormType == 0x34;	   }
		bool IsWeapon()			const noexcept { return FormType == 0x29;      }
		bool IsNote() 			const noexcept { return FormType == 0x30;	   }

		bool IsDeleted()		const noexcept { return (formFlags & 32) != 0;	   }
		bool IsIgnored() 		const noexcept { return (formFlags & 4096) != 0;   }
		bool IsInitialized() 	const noexcept { return (formFlags & 8) != 0;	   }

		bool IsDynamicForm()	const noexcept { return FormID >= 0xFF000000;  }
		bool IsGold()			const noexcept { return FormID == 0x0000000F;  }
		bool IsLockpick()		const noexcept { return FormID == 0x0000000A;  }
		bool IsPlayer() 		const noexcept { return FormID == 0x00000007;  }
		bool IsPlayerRef() 		const noexcept { return FormID == 0x00000014;  }

		uint32_t GetFormFlags() const noexcept { return formFlags; }
		uint32_t GetFormID()	const noexcept { return FormID; }
		uint8_t	 GetFormType()	const noexcept { return FormType; }
			
		bool Is(uint32_t a_formType) { return GetFormType() == a_formType; }

		int32_t		 GetGoldValue();
		const char*  GetName();
		float		 GetWeight();

		template <class T, class = std::enable_if_t<std::negation_v<std::disjunction<std::is_pointer<T>, std::is_reference<T>, std::is_const<T>, std::is_volatile<T>>>>>
		T* As() noexcept;

		template <class T, class = std::enable_if_t<std::negation_v<std::disjunction<std::is_pointer<T>, std::is_reference<T>, std::is_const<T>, std::is_volatile<T>>>>>
		const T* As() const noexcept;
	public:
		void*     sourceFiles;
		uint32_t  formFlags;
		uint32_t  FormID;
		uint16_t  inGameFormFlags;
		uint8_t   FormType;
	};
	static_assert(sizeof(TESForm) == 0x20);
}
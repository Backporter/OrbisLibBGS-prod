#include "../Favorites/Favorites.h"
#include "../CraftingSubMenus/InventoryPlugin.h"

namespace Favorites
{
	// item
	void ItemFavoritesSet(ConsoleRE::FavoritesMenu* a_this, ConsoleRE::GFxValue* datacontainer, ConsoleRE::InventoryEntryData* obj)
	{
		if (ItemData::Extend)
		{
			ConsoleRE::GFxMovieView* movie = a_this->uiMovie;
			uint32_t id = 0;

			ItemData::common    (datacontainer, movie, obj->form     );
			ItemData::Standard  (datacontainer, movie, obj->form, obj);
			ItemData::inv       (datacontainer, movie, obj->form, obj);
			ItemData::magic     (datacontainer, movie, obj->form     );
			
			xUtilty::CryptoHandler::GetCRC32(id, obj->GetDisplayName(), obj->form->FormID & 0x00FFFFFF);
			datacontainer->RegisterNumber("itemId", id);

			auto pluginList = InventoryPlugin::getPluginList();
			for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
				if (*iter)
					(*iter)(movie, datacontainer, obj);
		}
	}

	// magic/vampire
	void MagicFavoritesSet(ConsoleRE::GFxMovieRoot* movie, ConsoleRE::GFxValue* datacontainer, ConsoleRE::TESForm* a_form)
	{
		using namespace ConsoleRE;
		if (ItemData::Extend)
		{
			const char* m_formName = NULL;
			uint32_t id = 0;

			ItemData::common(datacontainer, movie, a_form);
			ItemData::magic(datacontainer, movie, a_form);

			ConsoleRE::TESFullName* m_formFullName = TES_RTTI(a_form, TESForm, TESFullName);

			if (m_formFullName)
				m_formName = m_formFullName->name.c_str();

			xUtilty::CryptoHandler::GetCRC32(id, m_formName, a_form->FormID & 0x00FFFFFF);
			datacontainer->RegisterNumber("itemId", id);
		}
	}
}
#include "scene/opening/OpeningDataStore.h"
#include "resource/Resources.h"

OpeningDataStore::OpeningDataStore()
	: DataStore()
	, listMenuItem_{
		getString(StringId::MenuItem3DMenuDemo),
		getString(StringId::MenuItemChapter05),
	}
{
}

OpeningDataStore::~OpeningDataStore()
{
}

const char *OpeningDataStore::getStringTitle() const
{
	return getString(StringId::TitleOpeningScene);
}

const std::vector<const char *> &OpeningDataStore::getOpeningMenuItemList() const
{
	return listMenuItem_;
}

double OpeningDataStore::getRadius() const
{
	return 2.0;
}

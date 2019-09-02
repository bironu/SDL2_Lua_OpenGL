#include "scene/opening/OpeningDataStore.h"
#include "resources/Resources.h"
#include "resources/StringId.h"

OpeningDataStore::OpeningDataStore(Resources &res)
	: DataStore(res)
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
	return getString(StringId::TitleOpning);
}

const std::vector<const char *> &OpeningDataStore::getOpeningMenuItemList() const
{
	return listMenuItem_;
}

double OpeningDataStore::getRadius() const
{
	return 2.0;
}

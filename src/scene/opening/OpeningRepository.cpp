#include "scene/opening/OpeningRepository.h"
#include "resources/Resources.h"
#include "resources/StringId.h"

OpeningRepository::OpeningRepository(Resources &res)
	: Repository(res)
	, listMenuItem_{
		getString(StringId::MenuItem3DMenuDemo),
		getString(StringId::MenuItemChapter05),
	}
{
}

OpeningRepository::~OpeningRepository()
{
}

const char *OpeningRepository::getStringTitle() const
{
	return getString(StringId::TitleOpning);
}

const std::vector<const char *> &OpeningRepository::getOpeningMenuItemList() const
{
	return listMenuItem_;
}

double OpeningRepository::getRadius() const
{
	return 2.0;
}

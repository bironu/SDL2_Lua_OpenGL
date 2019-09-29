#ifndef SCENE_OPENING_OPENINGREPOSITORY_H_
#define SCENE_OPENING_OPENINGREPOSITORY_H_

#include "../Repository.h"

class OpeningRepository : public Repository
{
public:
	OpeningRepository(Resources &res);
	virtual ~OpeningRepository() override;

	int getMenuFontSize() const { return 48; }
	int getTitleFontSize() const { return 96; }

	const char *getStringTitle() const;
	double getRadius() const;

	const std::vector<const char *> &getOpeningMenuItemList() const;

private:
	std::vector<const char *> listMenuItem_;
};

#endif // SCENE_OPENING_OPENINGREPOSITORY_H_

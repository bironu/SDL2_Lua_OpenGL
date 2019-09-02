#include "scene/DataStore.h"
#include "resource/Resources.h"
#include "gl/GLTexture.h"

DataStore::DataStore(Resources &res)
	: res_(res)
{
}

DataStore::~DataStore()
{
}

int DataStore::getWindowWidth() const
{
	return res_.getWindowWidth();
}

int DataStore::getWindowHeight() const
{
	return res_.getWindowHeight();
}

int DataStore::getScreenWidth() const
{
	return res_.getScreenWidth();
}

int DataStore::getScreenHeight() const
{
	return res_.getScreenHeight();
}

const char *DataStore::getFontFileName() const
{
	return res_.getFontFileName();
}

std::shared_ptr<SDL_::Image> DataStore::getImage(const std::string &id) const
{
	return res_.getImage(id);
}

const char *DataStore::getString(const std::string &id) const
{
	return res_.getString(id);
}

std::shared_ptr<Joystick> DataStore::getJoystick(int index) const
{
	return res_.getJoystick(index);
}

void DataStore::reload()
{
	res_.reload();
}

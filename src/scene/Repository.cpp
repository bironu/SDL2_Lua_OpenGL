#include "scene/Repository.h"
#include "resources/Resources.h"
#include "gl/GLTexture.h"

Repository::Repository(Resources &res)
	: res_(res)
{
}

Repository::~Repository()
{
}

int Repository::getWindowWidth() const
{
	return res_.getWindowWidth();
}

int Repository::getWindowHeight() const
{
	return res_.getWindowHeight();
}

int Repository::getScreenWidth() const
{
	return res_.getScreenWidth();
}

int Repository::getScreenHeight() const
{
	return res_.getScreenHeight();
}

const char *Repository::getFontFileName() const
{
	return res_.getFontFileName();
}

std::shared_ptr<SDL_::Image> Repository::getImage(const std::string &id) const
{
	return res_.getImage(id);
}

const char *Repository::getString(const std::string &id) const
{
	return res_.getString(id);
}

std::shared_ptr<Joystick> Repository::getJoystick(int index) const
{
	return res_.getJoystick(index);
}

void Repository::reload()
{
	res_.reload();
}

#ifndef SCENE_DATASTORE_H_
#define SCENE_DATASTORE_H_

#include "misc/Uncopyable.h"
#include <memory>
#include <string>
#include <vector>

namespace SDL_
{
class Image;
}

namespace GL_
{
class Texture;
}

class Joystick;
class Resources;
class DataStore
{
public:
	UNCOPYABLE(DataStore);
	DataStore(Resources &res);
	virtual ~DataStore();

	int getWindowWidth() const;
	int getWindowHeight() const;
	int getScreenWidth() const;
	int getScreenHeight() const;

	const char *getFontFileName() const;
	std::shared_ptr<SDL_::Image> getImage(const std::string &) const;
	const char *getString(const std::string &) const;
	std::shared_ptr<Joystick> getJoystick(int) const;

	void reload();

private:
	Resources &res_;
};

#endif // SCENE_DATASTORE_H_

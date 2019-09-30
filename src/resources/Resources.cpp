#include "resources/Resources.h"
#include "resources/MenuInfo.h"
#include "sdl/SDLImage.h"
#include "lua/sol.hpp"
#include "sdl/SDLJoystick.h"
#include <SDL2/SDL_events.h>
#include <cstring>

Resources::Resources()
	: windowWidth_()
	, windowHeight_()
	, screenWidth_()
	, screenHeight_()
	, lang_()
	, luaString_()
	, luaImage_()
	, mapImage_()
	, mapJoystick_()
{
}

Resources::~Resources()
{
}

std::shared_ptr<SDL_::Image> Resources::getImage(const std::string &id) const
{
	auto i = mapImage_.find(id);
	if (i != mapImage_.end()) {
		return i->second;
	}
	else {
		const char *imagePath = (*luaImage_)["images"][id.c_str()].get<const char *>();
		std::shared_ptr<SDL_::Image> image = std::make_shared<SDL_::Image>(imagePath);
		if (image) {
			mapImage_.insert(std::make_pair(id, image));
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Image ID not found. %s\n", id.c_str());
		}
		return image;
	}
}

const char *Resources::getString(const std::string &id) const
{
	const char *result = (*luaString_)["strings"][id.c_str()].get_or<const char *>(nullptr);
	if (!result) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "String ID not found. %s\n", id.c_str());
	}
	return result;
}

const char *Resources::getFontFileName() const
{
	return (*luaString_)["font_name"].get<const char *>();
}

void Resources::addJoyDevice(const SDL_JoyDeviceEvent &jdevice)
{
	mapJoystick_.insert(std::make_pair(jdevice.which, std::make_shared<Joystick>(jdevice.which)));
}

void Resources::removeJoyDevice(const SDL_JoyDeviceEvent &jdevice)
{
	for (auto &pair : mapJoystick_) {
		if(pair.second->getInstanceID() == jdevice.which) {
			mapJoystick_.erase(pair.first);
			break;
		}
	}
}

std::shared_ptr<Joystick> Resources::getJoystick(int index) const
{
	auto i = mapJoystick_.find(index);
	if (i != mapJoystick_.end()) {
		return i->second;
	}
	else {
		return nullptr;
	}
}

void Resources::loadString(const std::string &lang)
{
	const std::string langPath = "res/lua/lang/" + lang + ".lua";
	luaString_ = std::make_unique<sol::state>();
	luaString_->open_libraries(sol::lib::base, sol::lib::package);
	luaString_->script_file(langPath);
}

void Resources::loadImage(const std::string &lang)
{
	mapImage_.clear();
	const std::string imagePath = "res/lua/image/image.lua";
	luaImage_ = std::make_unique<sol::state>();
	luaImage_->open_libraries(sol::lib::base, sol::lib::package);
	luaImage_->script_file(imagePath);
}

void Resources::clearImage()
{
	mapImage_.clear();
}

void Resources::reload()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.script_file("res/lua/system.lua");

	windowWidth_ = lua["window"]["width"].get<int>();
	windowHeight_ = lua["window"]["height"].get<int>();
	screenWidth_ = lua["screen"]["width"].get<int>();
	screenHeight_ = lua["screen"]["height"].get<int>();
	lang_ = lua["system"]["lang"].get<const char *>();

	loadString(lang_);
	loadImage(lang_);
}

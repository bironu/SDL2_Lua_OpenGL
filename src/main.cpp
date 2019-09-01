#include "app/Application.h"
#include "sdl/SDLWindow.h"
#include "resource/Resources.h"
#include "task/TaskManager.h"
//#include "scene/opening/OpeningScene.h"
#include "scene/chapter05/Chapter05Scene.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_opengl.h>
#include <memory>

int main(int argc, char *argv[])
{
	//const std::vector<std::string> args(argv, argv+argc);

	Application app(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
	if(!app.isApplication()){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Init error. %s", SDL_GetError());
		return 1;
	}

	app.initGL();

	Resources res;
	res.reload();
	const int width = res.getWindowWidth();
	const int height = res.getWindowHeight();

	auto mainWindow = std::make_shared<SDL_::Window>("main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	app.registerMainWindow(mainWindow);
	auto size = mainWindow->getSize();
	res.setWindowWidth(size.get_width());
	res.setWindowHeight(size.get_height());

	app.registerNextSceneFunc([](Application &app, Resources &res, TaskManager &manager){
		return std::make_shared<chapter05::Chapter05Scene>(app, res, manager);
	});

	SDL_Log("GL_VERSION: %s\n", glGetString(GL_VERSION));
	SDL_Log("GL_SHADING_LANGUAGE_VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	TaskManager manager;
	return app.run(res, manager);
}

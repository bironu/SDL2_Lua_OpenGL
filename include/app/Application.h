#if !defined(APPLICATION_H_)
#define APPLICATION_H_

#include "misc/Uncopyable.h"
#include "scene/Scene.h"
#include <SDL2/SDL.h>
#include <memory>
#include <stack>
#include <vector>

namespace SDL_
{
class Window;
}

class Resources;
class TaskManager;
class Application final
{
public:
	UNCOPYABLE(Application);
	explicit Application(Uint32 flags);
	~Application();

	void registerMainWindow(std::shared_ptr<SDL_::Window> mainWindow);
	std::shared_ptr<SDL_::Window> getMainWindow();
	void registerWindow(std::shared_ptr<SDL_::Window> window);
	void unregisterWindow(std::shared_ptr<SDL_::Window> window);
	std::shared_ptr<SDL_::Window> getWindow(int id);

	void initGL();
	bool initSubSystem(Uint32 flags) { return ::SDL_InitSubSystem(flags) == 0; }
	void quitSubSystem(Uint32 flags) { ::SDL_QuitSubSystem(flags); }
	bool isApplication() const { return is_application_; }
	bool isTtf() const { return is_ttf_; }
	bool isImage() const { return is_image_; }
	bool isMixer() const { return is_mixer_; }
	int run(Resources &, TaskManager &manager);
	void clearResumeStack();

	void registerNextSceneFunc(FuncCreateScene nextScene)
	{
		nextScene_ = nextScene;
	}

	//static void waitFrame();
	void quit(const int val = 0);
	void updateWindow(Uint32 id);

	static uint32_t getTickCount() { return ::SDL_GetTicks(); }

private:
	bool handlePreEvent(Resources &res, TaskManager &manager, SDL_Event &);

	const bool is_application_;
	const bool is_ttf_;
	const bool is_image_;
	const bool is_mixer_;
	std::shared_ptr<Scene> currentScene_;
	std::stack<FuncCreateScene> stackFuncResumeScene_;
	std::vector<std::shared_ptr<SDL_::Window>> listWindow_;
	std::shared_ptr<SDL_::Window> mainWindow_;
	FuncCreateScene nextScene_;
	int return_code_;
};

#endif // APPLICATION_H_

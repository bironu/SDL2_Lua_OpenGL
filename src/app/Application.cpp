#include "app/Application.h"
#include "sdl/SDLWindow.h"
#include "resources/Resources.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

Application::Application(Uint32 flags)
	: is_application_(::SDL_Init(flags) == 0)
	, is_ttf_(::TTF_Init() == 0)
	, is_image_(::IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
	, is_mixer_(::Mix_Init(MIX_INIT_MP3))
	, currentScene_()
	, stackFuncResumeScene_()
	, listWindow_()
	, mainWindow_()
	, nextScene_()
	, return_code_(0)
{
}

Application::~Application()
{
	listWindow_.clear();
	if (isMixer()) {
		::Mix_Quit();
	}
	if (isImage()) {
		::IMG_Quit();
	}
	if (isTtf()){
		::TTF_Quit();
	}
	if (isApplication()){
		::SDL_Quit();
	}
}

void Application::registerMainWindow(std::shared_ptr<SDL_::Window> mainWindow)
{
	mainWindow_ = mainWindow;
	registerWindow(mainWindow);
}

std::shared_ptr<SDL_::Window> Application::getMainWindow()
{
	return mainWindow_;
}

void Application::registerWindow(std::shared_ptr<SDL_::Window> window)
{
	listWindow_.push_back(window);
}

void Application::unregisterWindow(std::shared_ptr<SDL_::Window> window)
{
	listWindow_.erase(std::remove(std::begin(listWindow_), std::end(listWindow_), window), std::end(listWindow_));
}

std::shared_ptr<SDL_::Window> Application::getWindow(int id)
{
	std::shared_ptr<SDL_::Window> result;
	for(auto window : listWindow_) {
		if(window->getWindowId() == id) {
			result = window;
			break;
		}
	}
	return result;
}

void Application::initGL()
{
	::SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	::SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	//::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	::SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	::SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    ::SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	::SDL_GL_SetSwapInterval(1);

	// ::glEnable(GL_TEXTURE_2D);
	// ::glEnable(GL_BLEND);
	// ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ::glClearColor(0.0, 0.0, 0.0, 0.0);
	// ::glCullFace(GL_BACK);
	// ::glFrontFace(GL_CCW);
	// ::glEnable(GL_CULL_FACE);
	// ::glEnable(GL_DEPTH_TEST);
	// ::glClearDepth(1.0);
	// ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

int Application::run(Resources &res, TaskManager &manager)
{
	currentScene_ = nextScene_(*this, res, manager);
	currentScene_->onCreate();
	nextScene_ = nullptr;

	SDL_Event event;
	bool idle(false);
	while(currentScene_) {
		if(::SDL_PollEvent(&event) != 0){
			if (!handlePreEvent(res, manager, event)) {
				currentScene_->dispatch(event);
			}
			idle = true;
		}
		else if (idle) {
			idle = currentScene_->onIdle(::SDL_GetTicks());
		}
		else {
			if (::SDL_WaitEvent(0) == 0){
				::SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_WaitEvent Error!! %s", ::SDL_GetError());
				quit(1);
			}
		}
		if (currentScene_ && currentScene_->isFinished()) {
			currentScene_->onDestroy();
			currentScene_.reset();
		}

		if (nextScene_) {
			if (currentScene_) {
				stackFuncResumeScene_.push(currentScene_->onSuspend());
			}
			currentScene_ = nextScene_(*this, res, manager);
			currentScene_->onCreate();
		}

		if (!currentScene_) {
			if(!stackFuncResumeScene_.empty()){
				auto funcResumeScene = stackFuncResumeScene_.top();
				stackFuncResumeScene_.pop();
				currentScene_ = funcResumeScene(*this, res, manager);
				currentScene_->onResume();
			}
		}
	}
	clearResumeStack();
	return return_code_;
}

void Application::clearResumeStack()
{
	while(!stackFuncResumeScene_.empty()){stackFuncResumeScene_.pop();}
}

void Application::quit(const int val)
{
	SDL_Event event = {SDL_QUIT};
	return_code_ = val;
	::SDL_PushEvent(&event);
}

void Application::updateWindow(Uint32 id)
{
	SDL_Event event = {SDL_WINDOWEVENT};
	event.window.windowID = id;
	event.window.event = SDL_WINDOWEVENT_EXPOSED;
	::SDL_PushEvent(&event);
}

bool Application::handlePreEvent(Resources &res, TaskManager &manager, SDL_Event &event)
{
	bool result = false;

	switch(event.type)
	{
	case SDL_QUIT:
		currentScene_.reset();
		clearResumeStack();
		nextScene_ = nullptr;
		result = true;
		break;

	case SDL_JOYDEVICEADDED:
		res.addJoyDevice(event.jdevice);
		//currentScene_->onAddJoystick(event.jdevice.which);
		break;

	case SDL_JOYDEVICEREMOVED:
		res.removeJoyDevice(event.jdevice);
		break;

	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			SDL_Log("Window %d shown", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			SDL_Log("Window %d hidden", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_Log("Window %d exposed", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_MOVED:
			SDL_Log("Window %d moved to %d,%d",
					event.window.windowID, event.window.data1, event.window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			res.setWindowWidth(event.window.data1);
			res.setWindowHeight(event.window.data2);
			SDL_Log("Window %d resized to %dx%d",
					event.window.windowID, event.window.data1, event.window.data2);
			calcViewPort(res);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			res.setWindowWidth(event.window.data1);
			res.setWindowHeight(event.window.data2);
			SDL_Log("Window %d size changed to %dx%d",
					event.window.windowID, event.window.data1, event.window.data2);
			calcViewPort(res);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			SDL_Log("Window %d minimized", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			SDL_Log("Window %d maximized", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			SDL_Log("Window %d restored", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_ENTER:
			SDL_Log("Mouse entered window %d", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			SDL_Log("Mouse left window %d", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			SDL_Log("Window %d gained keyboard focus", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			SDL_Log("Window %d lost keyboard focus", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			SDL_Log("Window %d closed", event.window.windowID);
			break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
		case SDL_WINDOWEVENT_TAKE_FOCUS:
			SDL_Log("Window %d is offered a focus", event.window.windowID);
			break;
		case SDL_WINDOWEVENT_HIT_TEST:
			SDL_Log("Window %d has a special hit test", event.window.windowID);
			break;
#endif
		default:
			SDL_Log("Window %d got unknown event %d",
					event.window.windowID, event.window.event);
			break;
		}
		break;

	default:
		break;
	}

	return result;
}

void Application::calcViewPort(Resources &res)
{
	const int ww = res.getWindowWidth();
	const int wh = res.getWindowHeight();
	const int sw = res.getScreenWidth();
	const int sh = res.getScreenHeight();
	if (static_cast<float>(ww)/static_cast<float>(wh) != static_cast<float>(sw)/static_cast<float>(sh)) {
		const auto waspect = static_cast<float>(ww)/static_cast<float>(sw);
		const auto haspect = static_cast<float>(wh)/static_cast<float>(sh);
		if(waspect > haspect) {
			auto pw = sw * haspect;
			auto ph = wh;
			::glViewport((ww-pw)/2, 0, pw, ph);
		}
		else {
			auto ph = sh * waspect;
			auto pw = ww;
			::glViewport(0, (wh-ph)/2, pw, ph);
		}
	}
	else {
		::glViewport(0, 0, ww, wh);
	}
}

//void Application::waitFrame()
//{
//	static const Uint32 wait((1000<<16)/60);
//	static Uint32 lasttime(0); // last time
//	static Uint32 passage(0);
//
//	const Uint32 t(::SDL_GetTicks()); // now time
//	const Uint32 progress(t - lasttime);
//	passage = (passage & 0xffff) + wait;
//	const Uint32 twait(passage >> 16);
//	if(progress >= twait){
//		lasttime = t;
//	}
//	else{
//		::SDL_Delay(twait-progress);
//		while((::SDL_GetTicks()-lasttime) < twait);
//		lasttime += twait;
//	}
//}

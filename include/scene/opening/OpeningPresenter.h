#ifndef SCENE_OPENING_OPENINGPRESENTER_H_
#define SCENE_OPENING_OPENINGPRESENTER_H_

#include "../Presenter.h"
#include "gl/widget/VerticalRotateMenu.h"
#include "sdl/SDLSoundMixer.h"
#include "sdl/SDLSoundChunk.h"
#include <vector>
#include <memory>

class Shader;
class VertexArray;

namespace GL_
{
class Sprite;
class BillBoard;
class Sprite2D;
class Sprite3D;
class TextView;
class GroupView;
class ScreenView;
}

class OpeningScene;
class OpeningDataStore;
class OpeningPresenter : public Presenter
{
public:
	OpeningPresenter(OpeningScene &scene, const OpeningDataStore &dataStore);
	virtual ~OpeningPresenter() override;

	virtual void exposed() override;

	bool moveCursor(int, int, bool);
	void action(uint32_t);
	void startMenuScene();
	void startChapter05Scene();

	void init();

private:
	static constexpr int ID_ROTATE_MENU = 200;

	bool loadShaders();
	void createSpriteVerts();

	OpeningScene &scene_;
	const OpeningDataStore &dataStore_;
	const std::vector<const char *> &listMenuItem_;
	GL_::VerticalRotateMenu rotateMenu_;
	SDL_::SoundMixer mixer_;
	SDL_::SoundChunk chunk_;

	std::shared_ptr<Shader> mSpriteShader;
	std::shared_ptr<VertexArray> mSpriteVerts;

};

#endif // SCENE_OPENING_OPENINGPRESENTER_H_

#ifndef WIDGET_HORIZONTALROTATEMENU_H_
#define WIDGET_HORIZONTALROTATEMENU_H_

#include "RotateMenu.h"

namespace GL_
{

class Sprite;
class HorizontalRotateMenu : public RotateMenu<Sprite>
{
public:
	HorizontalRotateMenu();
	virtual ~HorizontalRotateMenu() override;

	virtual void draw() override;
};

}
#endif // WIDGET_HORIZONTALROTATEMENU_H_

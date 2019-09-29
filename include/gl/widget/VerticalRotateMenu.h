#ifndef WIDGET_VERTICALROTATEMENU_H_
#define WIDGET_VERTICALROTATEMENU_H_

#include "RotateMenu.h"

namespace GL_ {

class Sprite;
class VerticalRotateMenu : public RotateMenu<Sprite>
{
public:
	VerticalRotateMenu();
	virtual ~VerticalRotateMenu() override;

	virtual void draw() override;
};

} // namespace GL_

#endif // WIDGET_VERTICALROTATEMENU_H_

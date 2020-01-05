#include "gl/view/GLViewOrigin.h"
#include "gl/view/GLView.h"
#include "gl/view/GLViewGroup.h"

namespace GL_
{

XOriginLeft xleft;
XOriginCenter xcenter;
XOriginRight xright;

YOriginTop ytop;
YOriginCenter ycenter;
YOriginBottom ybottom;

void XOriginLeft::alignLeft(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * -0.5f);
    }
}

void XOriginLeft::alignRight(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * 0.5f - view.getWidth());
    }
}

void XOriginLeft::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(view.getWidth() * -0.5f);
    }
}

float XOriginLeft::getLeft() const
{
    return 0.0f;
}

float XOriginLeft::getRight() const
{
    return 1.0f;
}

void XOriginCenter::alignLeft(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * -0.5f + view.getWidth() * 0.5f);
    }
}

void XOriginCenter::alignRight(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * 0.5f - view.getWidth() * 0.5f);
    }
}

void XOriginCenter::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(0.0f);
    }
}

float XOriginCenter::getLeft() const
{
    return -0.5f;
}

float XOriginCenter::getRight() const
{
    return 0.5f;
}

void XOriginRight::alignLeft(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * -0.5f + view.getWidth());
    }
}

void XOriginRight::alignRight(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(parent->getWidth() * 0.5f);
    }
}

void XOriginRight::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setXPos(view.getWidth() * 0.5f);
    }
}

float XOriginRight::getLeft() const
{
    return -1.0f;
}

float XOriginRight::getRight() const
{
    return 0.0f;
}

void YOriginTop::alignTop(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * 0.5f);
    }
}

void YOriginTop::alignBottom(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * -0.5f + view.getHeight());
    }
}

void YOriginTop::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(view.getHeight() * 0.5f);
    }
}

float YOriginTop::getTop() const
{
    return 0.0f;
}

float YOriginTop::getBottom() const
{
    return -1.0f;
}

void YOriginCenter::alignTop(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * 0.5f + view.getHeight() * -0.5f);
    }
}

void YOriginCenter::alignBottom(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * -0.5f + view.getHeight() * 0.5f);
    }
}

void YOriginCenter::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(0.0f);
    }
}

float YOriginCenter::getTop() const
{
    return 0.5f;
}

float YOriginCenter::getBottom() const
{
    return -0.5f;
}

void YOriginBottom::alignTop(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * 0.5f + view.getHeight() * -1.0f);
    }
}

void YOriginBottom::alignBottom(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(parent->getHeight() * -0.5f);
    }
}

void YOriginBottom::centering(View &view) const
{
    auto parent = view.getParent();
    if (parent) {
        view.setYPos(view.getHeight() * -0.5f);
    }
}

float YOriginBottom::getTop() const
{
    return 1.0f;
}

float YOriginBottom::getBottom() const
{
    return 0.0f;
}

} // GL_

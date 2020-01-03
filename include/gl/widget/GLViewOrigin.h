#pragma once
#if !defined(GLVIEWORIGIN_H_)
#define GLVIEWORIGIN_H_

namespace GL_
{

class View;
class XOrigin
{
public:
	XOrigin() = default;
	virtual ~XOrigin() = default;
	virtual void alignLeft(View &view) const = 0;
	virtual void alignRight(View &view) const = 0;
	virtual void centering(View &view) const = 0;
    virtual float getLeft() const = 0;
    virtual float getRight() const = 0;
};

class XOriginLeft : public XOrigin
{
public:
	XOriginLeft():XOrigin(){}
	virtual ~XOriginLeft() override = default;
	virtual void alignLeft(View &view) const override;
	virtual void alignRight(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getLeft() const override;
    virtual float getRight() const override;
};

class XOriginCenter : public XOrigin
{
public:
	XOriginCenter():XOrigin(){}
	virtual ~XOriginCenter() override = default;
	virtual void alignLeft(View &view) const override;
	virtual void alignRight(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getLeft() const override;
    virtual float getRight() const override;
};

class XOriginRight : public XOrigin
{
public:
	XOriginRight():XOrigin(){}
	virtual ~XOriginRight() override = default;
	virtual void alignLeft(View &view) const override;
	virtual void alignRight(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getLeft() const override;
    virtual float getRight() const override;
};

class YOrigin
{
public:
	YOrigin() = default;
	virtual ~YOrigin() = default;
	virtual void alignTop(View &view) const = 0;
	virtual void alignBottom(View &view) const = 0;
	virtual void centering(View &view) const = 0;
    virtual float getTop() const = 0;
    virtual float getBottom() const = 0;
};

class YOriginTop : public YOrigin
{
public:
	YOriginTop():YOrigin(){}
	virtual ~YOriginTop() override = default;
	virtual void alignTop(View &view) const override;
	virtual void alignBottom(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getTop() const override;
    virtual float getBottom() const override;
};

class YOriginCenter : public YOrigin
{
public:
	YOriginCenter():YOrigin(){}
	virtual ~YOriginCenter() override = default;
	virtual void alignTop(View &view) const override;
	virtual void alignBottom(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getTop() const override;
    virtual float getBottom() const override;
};

class YOriginBottom : public YOrigin
{
public:
	YOriginBottom():YOrigin(){}
	virtual ~YOriginBottom() override = default;
	virtual void alignTop(View &view) const override;
	virtual void alignBottom(View &view) const override;
	virtual void centering(View &view) const override;
    virtual float getTop() const override;
    virtual float getBottom() const override;
};

extern XOriginLeft xleft;
extern XOriginCenter xcenter;
extern XOriginRight xright;

extern YOriginTop ytop;
extern YOriginCenter ycenter;
extern YOriginBottom ybottom;

}

#endif // GLVIEWORIGIN_H_

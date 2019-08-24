#include "parts/Parts.h"

Parts::Parts(Scene &scene)
    : scene_(scene)
    , state_()
	, worldTransform_()
	, position_()
    , forward_()
    , up_()
    //, rotate_()
	, scale_()
	, isRecomputeWorldTransform_(true)
	, listComponent_()
{

}

Parts::~Parts()
{

}

void Parts::update(uint32_t tick)
{
	if (mState == EActive) {
		computeWorldTransform();
		updateComponents(tick);
		updateImpl(tick);
	}
}

void Parts::computeWorldTransform()
{
	if (isRecomputeWorldTransform_) {
		isRecomputeWorldTransform_ = false;
		// Scale, then rotate, then translate
		worldTransform_ = Matrix4::CreateScale(mScale);
		//worldTransform_ *= Matrix4::CreateRotationZ(mRotation);
		worldTransform_ *= Matrix4::CreateTranslation(position_);

		// Inform components world transform updated
		for (auto comp : listComponent_)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Parts::addComponent(std::shared_ptr<Component> component)
{
    listComponent_.push_back(component);
}

void Parts::removeComponent(std::shared_ptr<Component> component)
{
    listComponent_.remove(component);
}

void Parts::updateComponents(uint32_t tick)
{
	for (auto comp : listComponent_)
	{
		comp->update(tick);
	}
}

void Parts::updateImpl(uint32_t tick)
{

}

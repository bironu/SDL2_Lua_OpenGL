#pragma once
#if !defined(PARTS_PARTS_H_)
#define PARTS_PARTS_H_

#include "misc/Uncopyable.h"
#include <memory>
#include <stdint.h>

class Vector3;
class Matrix4;
class Scene;

namespace parts
{

enum class State
{
    Active,
    Paused,
    Dead,
};

class Component;
class Parts
{
public:
	Parts(Scene &scene);
	virtual ~Parts();

	void update(uint32_t tick);

	// getters/setters
	const Vector3& getPosition() const { return position_; }
	void setPosition(const Vector3& position) { position_ = position; isRecomputeWorldTransform_ = true; }
	float getScale() const { return scale_; }
	void setScale(float scale) { scale_ = scale;  isRecomputeWorldTransform_ = true; }
	//float GetRotation() const { return rotation_; }
	//void SetRotation(float rotation) { rotation_ = rotation;  isRecomputeWorldTransform_ = true; }
	
	void computeWorldTransform();
	const Matrix4& getWorldTransform() const { return worldTransform_; }

	const Vector3 &getForward() const { return forward_; }
    const Vector3 &getUp() const {return up_; }

	State getState() const { return state_; }
	void setState(State state) { state_ = state; }

	Scene &getScene() { return scene_; }

	// Add/remove components
	void addComponent(std::shared_ptr<Component> component);
	void removeComponent(std::shared_ptr<Component> component);
private:
	void updateComponents(uint32_t tick);
	virtual void updateImpl(uint32_t tick);

	Scene &scene_;

	// Actor's state
	State state_;

	// Transform
	Matrix4 worldTransform_;
	Vector3 position_; // 位置
    Vector3 forward_; // 前方向
    Vector3 up_; // 上方向
    //Quaternion rotate_; // 回転情報
	float scale_;
	bool isRecomputeWorldTransform_;

	std::vector<std::shared_ptr<Component>> listComponent_;
};

} // parts

#endif // PARTS_PARTS_H_

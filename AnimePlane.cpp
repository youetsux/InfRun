#include "Engine/Model.h"
#include "AnimePlane.h"


AnimePlane::AnimePlane(GameObject* parent)
	:GameObject(parent,"AnimePlane"),hmodel_(-1)
{
}

void AnimePlane::Initialize()
{
	hmodel_ = Model::Load("suv.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 0.1,0.1,0.1 };
	transform_.position_ = { 0, 0, 0 };
}

void AnimePlane::Update()
{
}

void AnimePlane::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void AnimePlane::Release()
{
}

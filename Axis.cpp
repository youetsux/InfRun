#include "Axis.h"
#include "Engine/Model.h"

Axis::Axis(GameObject* parent)
	:GameObject(parent, "Axis")
{
}

void Axis::Initialize()
{
	hmodel_ = Model::Load("axis.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 1,1,1 };
	transform_.position_ = { 0, 0, 0 };
}

void Axis::Update()
{
}

void Axis::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Axis::Release()
{
}

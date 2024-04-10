#include "Ground.h"
#include "Engine/Model.h"



Ground::Ground(GameObject* parent)
	:GameObject(parent,"Ground"), hmodel_(-1)
{
}

void Ground::Initialize()
{
	hmodel_ = Model::Load("Ground.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 1,1,1 };
	transform_.position_ = { 0, 0, 0 };

}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Ground::Release() 
{
}

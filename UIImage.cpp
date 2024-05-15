#include "UIImage.h"

UIImage::UIImage(GameObject* parent)
	:GameObject(parent,"UIImage"), readyImg_(-1), shouldRender_(false)
{

}

void UIImage::Initialize()
{
	readyImg_ = Image::Load("ready.png");
}

void UIImage::Update()
{
}

void UIImage::Draw()
{
	if (shouldRender_) {
		transform_.position_ = { 0, 0.5, 0 };
		Image::SetTransform(readyImg_, transform_);
		Image::Draw(readyImg_);
	}
}

void UIImage::Release()
{
	Image::Release(readyImg_);
}

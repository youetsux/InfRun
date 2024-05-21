#include "UIImage.h"
#include "CDTimer.h"
#include "Engine/Debug.h"

UIImage::UIImage(GameObject* parent)
	:GameObject(parent,"UIImage"), readyImg_(-1), shouldRender_(false),timer_(nullptr)
{

}

void UIImage::Initialize()
{
	cdNumImg_ = Image::Load("CdNumb.png");
	goImg_ = Image::Load("Go.png");
	readyImg_ = Image::Load("ready.png");
	assert(cdNumImg_ >= 0);
	assert(goImg_ >= 0);
	assert(readyImg_ >= 0);
}

void UIImage::Update()
{
}

void UIImage::Draw()
{
	if (shouldRender_) {
		readyTf_.position_ = { 0, 0.2, 0 };
		readyTf_.scale_ = { 0.5, 0.5, 1 };
		Image::SetTransform(readyImg_, readyTf_);
		Image::Draw(readyImg_);
		if (timer_->GetTime() < 4.0) {
			if (timer_->GetTime() > 1){
				cdNumTf_.position_ = { 0, -0.2, 0 };
				cdNumTf_.scale_ = { 0.8, 0.8, 1 };
				int num = (int)(timer_->GetTime()) - 1;
				Image::SetRect(cdNumImg_, (512/3.15)*num, 0, 512 / 3.15, 177);
				float a = timer_->GetTime();
				float nScale = 1.0  + (a - floor(a));
				cdNumTf_.scale_ = { nScale, nScale, 1 };
				Image::SetTransform(cdNumImg_, cdNumTf_);
				Image::Draw(cdNumImg_);
			}
			else
			{
				goTf_.position_ = { 0, -0.2, 0 };
				goTf_.scale_ = { 0.6, 0.6, 1 };
				Image::SetTransform(goImg_, goTf_);
				Image::Draw(goImg_);
			}
		}

	}
}

void UIImage::Release()
{
}

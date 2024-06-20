#include "Wanwan.h"
#include "Engine/Model.h"


Wanwan::Wanwan(GameObject* parent)
	:GameObject(parent,"Wanwan"),speed_(INIT_SPEED)
{
}

void Wanwan::Initialize()
{
	hmodel_ = Model::Load("cchomp3.fbx");
	assert(hmodel_ >= 0);

	transform_.scale_ = { 0.15, 0.15, 0.15 };
	transform_.position_ = { 0, 0.12, 20};
	transform_.rotate_ = { 0, 180, 0 };
	wss_ = WanwanSS::MOVE;
	Model::SetAnimFrame(hmodel_, WANWANFRAMES[wss_].first, WANWANFRAMES[wss_].second, 5.0);
	liveTime = 0;
	//XMStoreFloat4x4(&(t.matrix), transform_.GetWorldMatrix());
	//t.isLoop = false;
	//t.maxFrame = 50;
	//t.speed = 1.0;
	//mt = EFFEKSEERLIB::gEfk->Play("BOM", t);
	
}

void Wanwan::Update()
{
	liveTime++;
	if (liveTime == 30)
		liveTime = 0;
	//Model::ResetAnimeRenderState(hmodel_);
	//transform_.position_.z = transform_.position_.z - speed_;
}

void Wanwan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Wanwan::Release()
{
}

#include "Ossan.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "CDTimer.h"
#include "Ground.h"



Ossan::Ossan(GameObject* parent)
	:GameObject(parent, "Ossan"), hmodel_(-1),moveDir_(MAXDIR),cdtimer_(nullptr),ossanState_(IDLE)
{
}

void Ossan::Initialize()
{
	hmodel_ = Model::Load("human_texed.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 1,1,1 };
	transform_.position_ = { 0, 0, 0 };
	Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_]. first, OSFRAMES[ossanState_].second, 1 );
	cdtimer_ = new CDTimer(this, 5.0);
}


void Ossan::GetInputData()
{
	//moveDir_ = MOVEDIR::MAXDIR;
	//ossanState_ = OSS::IDLE;
	if (Input::IsKeyDown(DIK_W))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		moveDir_ = UP;
	}
	if (Input::IsKeyDown(DIK_A))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		moveDir_ = LEFT;
	}
	if (Input::IsKeyDown(DIK_S))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		moveDir_ = DOWN;
	}
	if (Input::IsKeyDown(DIK_D))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		moveDir_ = RIGHT;
	}
	if (Input::IsKeyDown(DIK_R))
	{
		transform_.rotate_.y -= 0.5f;
	}
	if (Input::IsKeyDown(DIK_T))
	{
		transform_.rotate_.y += 0.5f;
	}
	if (Input::IsKeyUp(DIK_SPACE))
	{
		ossanState_ = (OSS)((int)((ossanState_ + 1)%((int)MAXOSS)));
		Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_].first, OSFRAMES[ossanState_].second, 1);
	}
	if (Input::IsKeyUp(DIK_W) || Input::IsKeyUp(DIK_A) || Input::IsKeyUp(DIK_S) || Input::IsKeyUp(DIK_D))
	{
		if (ossanState_ == RUN) {
			Model::SetAnimFrame(hmodel_, OSFRAMES[IDLE].first, OSFRAMES[IDLE].second, 1);
			ossanState_ = OSS::IDLE;
		}
	}
	
}

XMVECTOR Ossan::GetMoveVec()
{
	static XMFLOAT3 oldPos = transform_.position_;
	XMVECTOR mV = XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&oldPos) ;
	oldPos = transform_.position_;

	return mV;
}

void Ossan::Update()
{
	//tr.rotate_.y += 0.5;
	Ground* yuka = (Ground*)FindObject("Ground");
	
	GetInputData();
	float speed = MOVESPEED;

	switch(ossanState_){
		case OSS::IDLE:
			speed = 0;
			break;
		case OSS::RUN:
			speed = MOVESPEED;
			break;
		case OSS::SPRINT:
			speed = MOVESPEED;
			break;
		case OSS::JUMP:
		case OSS::RPUNCH:
		case OSS::LPUNCH:
		case OSS::MAXOSS:
		default:
			speed = 0;
	}
	XMVECTOR tmp = XMLoadFloat3(&transform_.position_) + speed * XMLoadFloat3(&MDVEC[moveDir_]);
	float tmpy = XMVectorGetByIndex(tmp, 1);
	RayCastData p;
	p.start = { this->transform_.position_.x, transform_.position_.y + 100, transform_.position_.z };
	p.dir = { 0,-1,0 };
	Model::RayCast(yuka->GetModelNum(), &p);
	//Debug::Log(p.hit, true);
	tmpy = tmpy - p.dist + 100;
	tmp = XMVectorSetByIndex(tmp, tmpy, 1);

	//cdtimer_->Update();
	//Debug::Log((float)(cdtimer_->GetTime()), true);
	//static double timerTime = 5.0;
	//if (cdtimer_->IsTimeOver())
	//	cdtimer_->SetInitTime(timerTime + 2.0);
	XMStoreFloat3(&transform_.position_ ,tmp);
	transform_.rotate_.y = ROTANGLE[moveDir_];
	//Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_].first, OSFRAMES[ossanState_].second, 1);
}

void Ossan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Ossan::Release()
{
}

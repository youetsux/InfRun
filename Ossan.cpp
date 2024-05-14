#include "Ossan.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "CDTimer.h"
#include "Ground.h"
#include "DirectXMath.h"



Ossan::Ossan(GameObject* parent)
	:GameObject(parent, "Ossan"), hmodel_(-1),moveDir_(MAXDIR),cdtimer_(nullptr),ossanState_(OSS::IDLE),oldState_(OSS::IDLE)
{
}

void Ossan::SetIdleState() {
	ossanState_ = OSS::IDLE; Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_].first, OSFRAMES[ossanState_].second, 1);
}
void Ossan::SetRunState() {
	ossanState_ = OSS::RUN; Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_].first, OSFRAMES[ossanState_].second, 1);
}
void Ossan::SetDefeetState() { ossanState_ = OSS::DEFEET; }
void Ossan::SetTraversalState() { ossanState_ = OSS::TRAVERSAL; }

void Ossan::Initialize()
{
	hmodel_ = Model::Load("man_run.fbx");
	assert(hmodel_ >= 0);
	transform_.scale_ = { 0.1f, 0.1f, 0.1f };
	transform_.position_ = { 0.0f, 0.0f, 0.0f };
	posState_ = OCENTER;
	Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_]. first, OSFRAMES[ossanState_].second, 1.5 );
	cdtimer_ = new CDTimer(this, TRAVERSAL_TIME);
}


void Ossan::GetInputData()
{
	OPOS_STATE oldstate = posState_;
	if (isTraverasal()) {
		oldState_ = ossanState_;
		return;//ˆÚ“®’†‚È‚ç“ü—ÍŽó•t‚µ‚È‚¢
	}

	if (Input::IsKeyDown(DIK_A) || Input::IsKeyDown(DIK_LEFT))
	{
		if (ossanState_ != RUN) {
			oldState_ = ossanState_;
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		posState_ = posSetter(ILEFT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			oldState_ = ossanState_;
			ossanState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	if (Input::IsKeyDown(DIK_D) || Input::IsKeyDown(DIK_RIGHT))
	{
		if (ossanState_ != RUN) {
			oldState_ = ossanState_;
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		posState_ = posSetter(IRIGHT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			oldState_ = ossanState_;
			ossanState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	//transform_.position_ = REF_POS[posState_];
	if (Input::IsKeyUp(DIK_SPACE))
	{
		oldState_ = ossanState_;
		ossanState_ = (OSS)((int)((ossanState_ + 1)%((int)MAXOSS)));
		Model::SetAnimFrame(hmodel_, OSFRAMES[ossanState_].first, OSFRAMES[ossanState_].second, 1);
	}
}

OPOS_STATE Ossan::posSetter(INPUT_STATE inputDir)
{
	int posTmp = (int)posState_;
	int inputVal[3]{ -1, 1, 0 };
	
	posTmp = posTmp + inputVal[inputDir];
	if (posTmp < 0)
		posTmp = OPOS_STATE::OLEFT;
	if (posTmp >= OPOS_STATE::MAXPOS)
		posTmp = OPOS_STATE::ORIGHT;
	return (OPOS_STATE)posTmp;
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
	OPOS_STATE oldPos = posState_;
	GetInputData();
	float speed = MOVESPEED;

	float lerpTime = (float)(cdtimer_->GetTime());
	if (lerpTime <= 0)
	{
		ossanState_ = RUN;
		lerpTime = 0;
	}

	if (ossanState_ == TRAVERSAL) {
		float lerpRate = 1.0f - lerpTime / TRAVERSAL_TIME;
		static XMVECTOR sourcePos;
		static XMVECTOR targetPos;

		if (oldState_ != TRAVERSAL) {
			sourcePos = XMLoadFloat3(&REF_POS[oldPos]);
			targetPos = XMLoadFloat3(&REF_POS[posState_]);
		}
		XMVECTOR lpos = XMVectorLerp(sourcePos, targetPos, lerpRate);

		float rotAngle = TR_ROTANGLE*sin(lerpRate * XM_PI);
		if (XMVectorGetX(sourcePos) > XMVectorGetX(targetPos))
			rotAngle = -rotAngle;
		XMStoreFloat3(&(transform_.position_), lpos);
		transform_.rotate_.y = rotAngle;
	}
	else
	{
		transform_.rotate_.y = 0.0f;
		transform_.position_ = REF_POS[posState_];
	}
	//Model::ResetAnimeRenderState(hmodel_);
	cdtimer_->Update();

}

void Ossan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Ossan::Release()
{
}

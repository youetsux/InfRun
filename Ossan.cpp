#include "Ossan.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "CDTimer.h"
#include "Ground.h"
#include "DirectXMath.h"



Ossan::Ossan(GameObject* parent)
	:GameObject(parent, "Ossan"), hmodel_(-1),moveDir_(MAXDIR),cdtimer_(nullptr),ossanState_(IDLE)
{
}

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
	if (isTraverasal())
		return;//ˆÚ“®’†‚È‚ç“ü—ÍŽó•t‚µ‚È‚¢

	if (Input::IsKeyDown(DIK_A) || Input::IsKeyDown(DIK_LEFT))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		posState_ = posSetter(ILEFT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			ossanState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	if (Input::IsKeyDown(DIK_D) || Input::IsKeyDown(DIK_RIGHT))
	{
		if (ossanState_ != RUN) {
			ossanState_ = RUN;
			Model::SetAnimFrame(hmodel_, OSFRAMES[RUN].first, OSFRAMES[RUN].second, 1);
		}
		posState_ = posSetter(IRIGHT);
		moveDir_ = UP;
		if (posState_ != oldstate) {
			ossanState_ = TRAVERSAL;
			cdtimer_->ResetTimer();
			cdtimer_->StartTimer();
		}
	}
	//transform_.position_ = REF_POS[posState_];
	if (Input::IsKeyUp(DIK_SPACE))
	{
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
	GetInputData();
	float speed = MOVESPEED;

	cdtimer_->Update();

	float lerpTime = (float)(cdtimer_->GetTime());
	static bool isMoving = false;
	if (lerpTime <= 0)
	{
		ossanState_ = RUN;
		lerpTime = 0;
		isMoving = false;
	}

	if (ossanState_ == TRAVERSAL) {
		float lerpRate = 1.0f - lerpTime / TRAVERSAL_TIME;
		static XMVECTOR sourcePos, targetPos;
		float rotAngle;

		if (isMoving == false) {
			isMoving = true;
			sourcePos = XMLoadFloat3(&transform_.position_);
			targetPos = XMLoadFloat3(&REF_POS[posState_]);
		}
		XMVECTOR lpos = XMVectorLerp(sourcePos, targetPos, lerpRate);

		rotAngle = TRAVERSAL_ANGLE * sin(lerpRate * XM_PI);
		if (XMVectorGetX(sourcePos) > XMVectorGetX(targetPos))
			rotAngle = -rotAngle;

		XMStoreFloat3(&(transform_.position_), lpos);
		transform_.rotate_.y = rotAngle;
	}
	else
	{
		transform_.position_ = REF_POS[posState_];
	}
	//switch(ossanState_){
	//	case OSS::IDLE:
	//		speed = 0;
	//		break;
	//	case OSS::RUN:
	//		speed = 0;
	//		break;
	//	case OSS::DEFEET:
	//		break;
	//	case OSS::MAXOSS:
	//	default:
	//		speed = 0;
	//}

}

void Ossan::Draw()
{
	Model::SetTransform(hmodel_, transform_);
	Model::Draw(hmodel_);
}

void Ossan::Release()
{
}

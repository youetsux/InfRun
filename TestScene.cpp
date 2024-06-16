#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Ossan.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Wanwan.h"
#include "wanwanGenerator.h"
#include "Engine/Debug.h"


namespace {
	const XMFLOAT3 INITCAMPOS{ 0, 1, -1.5 };
	//const XMFLOAT3 INITCAMPOS{ 0, 0.5, 0.1 };
	
}



void TestScene::PlayUpdate()
{
	if (timer_->IsTimeOver())
	{
		wang->Generate();
		timer_->ResetTimer();
		timer_->StartTimer();
	}
	timer_->Update();
}

void TestScene::ReadyUpdate()
{
	
	if (timer_->IsTimeOver())
	{
		PSTATE = PLAY;
		player->SetRunState();
		ground->StartScroll();
		uiImage_->DisableRender();
		uiImage_->KillMe();
		wang = Instantiate<wanwanGenerator>(this);
		wang->SetSpeed(0.1f);
		
		timer_->SetInitTime(GPERIODS[PSTATE]);
		timer_->StartTimer();
	}
	
	timer_->Update();
}

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),timer_(nullptr),PSTATE(READY)
{
}

//������
void TestScene::Initialize()
{

	timer_ = new CDTimer(this, GPERIODS[READY]);

	Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);

	player = Instantiate<Ossan>(this);
	XMFLOAT3 pos = player->GetWorldPosition();
	Camera::SetTarget({ 0.0f, 0.2f, 2.0f });
	uiImage_ = Instantiate<UIImage>(this);
	uiImage_->EnableRender();
	uiImage_->SetTimerInstance(timer_);
	
}


//�X�V
void TestScene::Update()
{
	switch (PSTATE)
	{
	case READY:
		ReadyUpdate();
		break;
	case PLAY:
		PlayUpdate();
		break;
	case DEAD:
		break;
	default:
		return;
	}
}

//�`��//
void TestScene::Draw()
{
	switch (PSTATE)
	{
	case READY:
		break;
	case PLAY:
		break;
	case DEAD:
		break;
	default:
		return;
	}
	
}

//�J��
void TestScene::Release()
{
}

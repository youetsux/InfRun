#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Ossan.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Wanwan.h"
#include "wanwanGenerator.h"

const XMFLOAT3 INITCAMPOS{ 0, 1, -1.5 };
//const XMFLOAT3 INITCAMPOS{ 0, 0.5, 0.1 };


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),timer_(nullptr)
{
}

//初期化
void TestScene::Initialize()
{
	timer_ = new CDTimer(this, GENTIME);


	Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);

	player = Instantiate<Ossan>(this);
	XMFLOAT3 pos = player->GetWorldPosition();

	wang = Instantiate<wanwanGenerator>(this);
	Camera::SetTarget({ 0.0f, 0.2f, 2.0f });
	timer_->StartTimer();
	wang->SetSpeed(0.05f);
}

//更新
void TestScene::Update()
{
	if (timer_->IsTimeOver())
	{
		wang->Generate();
		timer_->ResetTimer();
		timer_->StartTimer();
	}
	timer_->Update();
	//XMVECTOR tVec = player->GetMoveVec();

	//XMStoreFloat3(&camPos_, XMLoadFloat3(&camPos_) + tVec);
	//XMFLOAT3 pos = player->GetWorldPosition();

	//Camera::SetPosition(camPos_);
	//Camera::SetTarget({ pos.x ,pos.y + 0.5f, pos.z });
}

//描画//
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}

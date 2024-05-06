#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Ossan.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Wanwan.h"

const XMFLOAT3 INITCAMPOS{ 0, 0.5, -1.0 };
//const XMFLOAT3 INITCAMPOS{ 0, 0.5, 0.1 };


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{

	Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);

	player = Instantiate<Ossan>(this);
	XMFLOAT3 pos = player->GetWorldPosition();

	Instantiate<Wanwan>(this);
	//Camera::SetTarget({pos.x ,pos.y+1.0f, pos.z });
	Camera::SetTarget({ 0.0f, 0.2f, 2.0f });

	//Camera::SetTarget({ 0, 0, 0 });
}

//更新
void TestScene::Update()
{
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

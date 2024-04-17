#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "AnimePlane.h"
#include "Engine/Debug.h"
#include "Axis.h"

const XMFLOAT3 INITCAMPOS{ 20, 25, 50 };


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Axis>(this);
	player = Instantiate<AnimePlane>(this);
	//Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);
	//XMFLOAT3 pos = player->GetWorldPosition();
	Camera::SetTarget({ 0,0,0 });
}

//更新
void TestScene::Update()
{

}

//描画//
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}

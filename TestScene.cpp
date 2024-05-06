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


//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
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

//�X�V
void TestScene::Update()
{
	//XMVECTOR tVec = player->GetMoveVec();

	//XMStoreFloat3(&camPos_, XMLoadFloat3(&camPos_) + tVec);
	//XMFLOAT3 pos = player->GetWorldPosition();

	//Camera::SetPosition(camPos_);
	//Camera::SetTarget({ pos.x ,pos.y + 0.5f, pos.z });
}

//�`��//
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}

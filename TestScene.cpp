#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "AnimePlane.h"
#include "Engine/Debug.h"
#include "Axis.h"

const XMFLOAT3 INITCAMPOS{ 20, 25, 50 };


//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
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

//�X�V
void TestScene::Update()
{

}

//�`��//
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}

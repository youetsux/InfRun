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
#include "Engine/Direct3D.h"

#include <Effekseer.h>
#include <../EffekseerRendererDX11/EffekseerRendererDX11.h>


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

	ground = Instantiate<Ground>(this);
	camPos_ = INITCAMPOS;
	Camera::SetPosition(camPos_);

	player = Instantiate<Ossan>(this);
	XMFLOAT3 pos = player->GetWorldPosition();
	Camera::SetTarget({ 0.0f, 0.2f, 2.0f });
	uiImage_ = Instantiate<UIImage>(this);
	uiImage_->EnableRender();
	uiImage_->SetTimerInstance(timer_);

	
	// Create a manager of effects
	// �G�t�F�N�g�̃}�l�[�W���[�̍쐬
	auto efkManager = ::Effekseer::Manager::Create(8000);


	auto efkRenderer = Direct3D::GetEffekseerRenderer();

	// Specify a position of view
	// ���_�ʒu���m��
	auto viewerPosition = ::Effekseer::Vector3D(camPos_.x,camPos_.y, camPos_.z);

	// Specify a projection matrix
	// ���e�s���ݒ�
	Effekseer::Matrix44 MProj = Effekseer::Matrix44().PerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	efkRenderer->SetProjectionMatrix(MProj);

	// Specify a camera matrix
	// �J�����s���ݒ�
	Effekseer::Matrix44 cameraMatrix;
	cameraMatrix.LookAtLH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
	efkRenderer->SetCameraMatrix(cameraMatrix);

	// Load an effect
	// �G�t�F�N�g�̓Ǎ�
	Direct3D::g_effect = Effekseer::Effect::Create(efkManager,  u"Laser01_reload.efkefc");
		
}


void TestScene::EffectDraw()
{

	static int32_t time = 0;
	Effekseer::Handle efkHandle = 0;

	if (time % 120 == 0)
	{
		// Play an effect
		// �G�t�F�N�g�̍Đ�
		efkHandle = Direct3D::g_manager->Play(Direct3D::g_effect, 0, 2, 0);
	}

	if (time % 120 == 119)
	{
		// Stop effects
		// �G�t�F�N�g�̒�~
		Direct3D::g_manager->StopEffect(efkHandle);
		time = 0;
	}

	// Move the effect
	// �G�t�F�N�g�̈ړ�
	Direct3D::g_manager->AddLocation(efkHandle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// Set layer parameters
	// ���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = Effekseer::Vector3D{ camPos_.x,camPos_.y,camPos_.z };
	Direct3D::g_manager->SetLayerParameter(0, layerParameter);

	//// Update the manager
	//// �}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	Direct3D::g_manager->Update(updateParameter);

	//// Execute functions about DirectX
	//// DirectX�̏���
	//device.ClearScreen();

	//// Update a time
	//// ���Ԃ��X�V����
	Direct3D::g_renderer->SetTime(time / 60.0f);

	//// Specify a projection matrix
	//// ���e�s���ݒ�
	//efkRenderer->SetProjectionMatrix(projectionMatrix);

	//// Specify a camera matrix
	//// �J�����s���ݒ�
	//efkRenderer->SetCameraMatrix(cameraMatrix);

	//// Begin to rendering effects
	//// �G�t�F�N�g�̕`��J�n�������s���B
	//efkRenderer->BeginRendering();

	Direct3D::g_renderer->BeginRendering();


	//// Render effects
	//// �G�t�F�N�g�̕`����s���B
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix = Direct3D::g_renderer->GetCameraProjectionMatrix();
	Direct3D::g_manager->Draw(drawParameter);

	//// Finish to rendering effects
	//// �G�t�F�N�g�̕`��I���������s���B
	//efkRenderer->EndRendering();
	Direct3D::g_renderer->EndRendering();

	time++;
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
		EffectDraw();
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

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



//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene"),timer_(nullptr),PSTATE(READY)
{
}

//初期化
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
	// エフェクトのマネージャーの作成
	auto efkManager = ::Effekseer::Manager::Create(8000);


	auto efkRenderer = Direct3D::GetEffekseerRenderer();

	// Specify a position of view
	// 視点位置を確定
	auto viewerPosition = ::Effekseer::Vector3D(camPos_.x,camPos_.y, camPos_.z);

	// Specify a projection matrix
	// 投影行列を設定
	Effekseer::Matrix44 MProj = Effekseer::Matrix44().PerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	efkRenderer->SetProjectionMatrix(MProj);

	// Specify a camera matrix
	// カメラ行列を設定
	Effekseer::Matrix44 cameraMatrix;
	cameraMatrix.LookAtLH(viewerPosition, ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f));
	efkRenderer->SetCameraMatrix(cameraMatrix);

	// Load an effect
	// エフェクトの読込
	Direct3D::g_effect = Effekseer::Effect::Create(efkManager,  u"Laser01_reload.efkefc");
		
}


void TestScene::EffectDraw()
{

	static int32_t time = 0;
	Effekseer::Handle efkHandle = 0;

	if (time % 120 == 0)
	{
		// Play an effect
		// エフェクトの再生
		efkHandle = Direct3D::g_manager->Play(Direct3D::g_effect, 0, 2, 0);
	}

	if (time % 120 == 119)
	{
		// Stop effects
		// エフェクトの停止
		Direct3D::g_manager->StopEffect(efkHandle);
		time = 0;
	}

	// Move the effect
	// エフェクトの移動
	Direct3D::g_manager->AddLocation(efkHandle, ::Effekseer::Vector3D(0.2f, 0.0f, 0.0f));

	// Set layer parameters
	// レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = Effekseer::Vector3D{ camPos_.x,camPos_.y,camPos_.z };
	Direct3D::g_manager->SetLayerParameter(0, layerParameter);

	//// Update the manager
	//// マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	Direct3D::g_manager->Update(updateParameter);

	//// Execute functions about DirectX
	//// DirectXの処理
	//device.ClearScreen();

	//// Update a time
	//// 時間を更新する
	Direct3D::g_renderer->SetTime(time / 60.0f);

	//// Specify a projection matrix
	//// 投影行列を設定
	//efkRenderer->SetProjectionMatrix(projectionMatrix);

	//// Specify a camera matrix
	//// カメラ行列を設定
	//efkRenderer->SetCameraMatrix(cameraMatrix);

	//// Begin to rendering effects
	//// エフェクトの描画開始処理を行う。
	//efkRenderer->BeginRendering();

	Direct3D::g_renderer->BeginRendering();


	//// Render effects
	//// エフェクトの描画を行う。
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix = Direct3D::g_renderer->GetCameraProjectionMatrix();
	Direct3D::g_manager->Draw(drawParameter);

	//// Finish to rendering effects
	//// エフェクトの描画終了処理を行う。
	//efkRenderer->EndRendering();
	Direct3D::g_renderer->EndRendering();

	time++;
}

//更新
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

//描画//
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

//開放
void TestScene::Release()
{
}

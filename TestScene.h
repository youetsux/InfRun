#pragma once
#include "Engine/GameObject.h"
#include "CDTimer.h"
#include "wanwanGenerator.h"
#include "UIImage.h"

namespace
{
	enum PLAYSTATE
	{
		READY, PLAY, DEAD, PMAX
	};
	const float GPERIODS[PMAX]{ 10.0, 1.0, 5.0 };
}


class Ossan;
class Ground;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	int msgBoard_;
	Ossan* player;
	Ground* ground;
	XMFLOAT3 camPos_;
	CDTimer*timer_;
	wanwanGenerator* wang;
	PLAYSTATE PSTATE;
	UIImage* uiImage_;
public:
	void PlayUpdate();
	void ReadyUpdate();
	//void EffectDraw();

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
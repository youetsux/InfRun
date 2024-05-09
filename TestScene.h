#pragma once
#include "Engine/GameObject.h"
#include "CDTimer.h"
#include "wanwanGenerator.h"

class Ossan;
class Ground;
//テストシーンを管理するクラス
class TestScene : public GameObject
{
	Ossan* player;
	Ground* ground;
	XMFLOAT3 camPos_;
	CDTimer*timer_;
	wanwanGenerator* wang;
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
#pragma once
#include "Engine/GameObject.h"


namespace
{
	enum WanwanSS
	{
		IDLE, MOVE, MAX
	};


	float INIT_SPEED = 0.01f;
	std::pair<int, int> WANWANFRAMES[MAX]
	{
		{0,0}, { 0,40 }
	};

}


class Wanwan :
    public GameObject
{
	int hmodel_;
	WanwanSS wss_;

	Transform wanwans[3];
	float speed_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Wanwan(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


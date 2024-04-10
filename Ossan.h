#pragma once
#include "Engine/GameObject.h"



enum OSS
{
	IDLE,JUMPUP,JUMPDOWN,JUMP,RUN,SPRINT,RPUNCH,LPUNCH,MAXOSS
};

class CDTimer;

namespace
{
	enum MOVEDIR
	{
		UP, LEFT, DOWN, RIGHT, MAXDIR
	};
	XMFLOAT3 MDVEC[MAXDIR + 1]
	{
		{0,0,1},{-1,0,0},{0,0,-1},{1,0,0},{0,0,0}
	};
	float MOVESPEED = 0.2f;
	std::pair<int, int> OSFRAMES[MAXOSS]
	{
		{1,105},{106,130},{131,155},{156,226},{308,347},{348,383},{384,438},{439,500}
	};
	const XMFLOAT3 INITDIR{ 0,0,1 };
	const float ROTANGLE[5]{ 180, 90, 0, 270, 0 };
}


//OST_IDLE		1-105
//OST_JUMPUP	106-130
//OST_JUMPDOWN	131-155
//OST_JUMP		156-226
//OST_RUN		308-347
//OST_SPRINT	348-383
//OST_RIGHTPUNCH	384-438
//OST_LEFTPUNCH		439-500
//テストシーンを管理するクラス
class Ossan : public GameObject
{
	int hmodel_;
	void GetInputData();
	MOVEDIR moveDir_;
	OSS ossanState_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ossan(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
public:
	XMVECTOR GetMoveVec();
	CDTimer* cdtimer_;
};
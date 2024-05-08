#pragma once
#include "Engine/GameObject.h"
#include "Wanwan.h"
#include <vector>


using std::vector;

namespace {
	std::pair<int, int> GENPAIR[] = { {1,2},{0,2},{0,1} };
	const XMFLOAT3 WAN_POS[3]{ {-0.35f, 0.0f, 20.0f}, {0.0f,0.0f,20.0f}, {0.35f,0.0f,20.0f} };
	const float GENTIME{ 1.0 };
}

class wanwanGenerator :
    public GameObject
{
	bool isGenerated_;
	int spaceLane_;
	int oldLane_;
	int GenerateNum(int _n);
	//vector<Wanwan*> wanList;
	vector<Transform> wanList;
	Wanwan* wan_;
	float speed_;
public:
	void Generate();
	void SetSpeed(float _speed);
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	wanwanGenerator(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


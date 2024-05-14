#pragma once
#include "Engine/GameObject.h"
#include <vector>

const int ROAD_NUM{ 25 };
const float GSPEED{ 0.01f };



//テストシーンを管理するクラス
class Ground : public GameObject
{

	int hmodel_;
	std::vector<Transform> gt;
	float scrollSpeed_;
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	int GetModelNum() { return hmodel_; }
	void SetScroolSpeed(float _speed) { scrollSpeed_ = _speed; }
};
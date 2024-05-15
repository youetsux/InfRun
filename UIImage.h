#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
class UIImage :
    public GameObject
{
	int readyImg_;
	bool shouldRender_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	UIImage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void EnableRender() { shouldRender_ = true; }
	void DisableRender() { shouldRender_ = false; }
};


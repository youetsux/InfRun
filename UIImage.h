#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"


class CDTimer;
class UIImage :
    public GameObject
{
	bool shouldRender_;
	int readyImg_;
	Transform readyTf_;
	int cdNumImg_;
	Transform cdNumTf_;
	int goImg_;
	Transform goTf_;
	CDTimer* timer_;
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
	void SetTimerInstance(CDTimer* _timer) {timer_ = _timer;}
};


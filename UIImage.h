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
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UIImage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void EnableRender() { shouldRender_ = true; }
	void DisableRender() { shouldRender_ = false; }
	void SetTimerInstance(CDTimer* _timer) {timer_ = _timer;}
};


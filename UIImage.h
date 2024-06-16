#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"
class UIImage :
    public GameObject
{
	int readyImg_;
	bool shouldRender_;
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
};


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
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Wanwan(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


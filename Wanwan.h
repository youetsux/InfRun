#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/EffekseerVFX.h"

namespace
{
	enum WanwanSS
	{
		IDLE, MOVE, MAX
	};


	float INIT_SPEED = 0.01f;
	std::pair<int, int> WANWANFRAMES[MAX]
	{
		{0,0}, { 0,120 }
	};

}


class Wanwan :
    public GameObject
{
	int hmodel_;
	WanwanSS wss_;

	Transform wanwans[3];
	float speed_;
	int liveTime;
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
	bool BomFlag() { return(liveTime == 0); }
	std::shared_ptr<EFFEKSEERLIB::EFKTransform> t;

};


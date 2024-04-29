#pragma once
#include "Engine/GameObject.h"

//IDLE 0-147
//RUN 148-186

enum OSS
{
	IDLE,RUN,DEFEET,MAXOSS
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
	float MOVESPEED = 0.01f;
	std::pair<int, int> OSFRAMES[MAXOSS]
	{
		{0,147},{148,186},{148,186}
	};
	const XMFLOAT3 INITDIR{ 0,0,1 };
	const float ROTANGLE[5]{ 0, -90, 180, 90, 0 };
}


//OST_IDLE		1-105
//OST_JUMPUP	106-130
//OST_JUMPDOWN	131-155
//OST_JUMP		156-226
//OST_RUN		308-347
//OST_SPRINT	348-383
//OST_RIGHTPUNCH	384-438
//OST_LEFTPUNCH		439-500
//�e�X�g�V�[�����Ǘ�����N���X
class Ossan : public GameObject
{
	int hmodel_;
	void GetInputData();
	MOVEDIR moveDir_;
	OSS ossanState_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ossan(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
public:
	XMVECTOR GetMoveVec();
	CDTimer* cdtimer_;
};
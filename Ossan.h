#pragma once
#include "Engine/GameObject.h"

//IDLE 0-147
//RUN 148-186

enum OSS
{
	IDLE,RUN,DEFEET,TRAVERSAL,MAXOSS
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
		{0,147},{148,186},{148,186}, {0,147}
	};
	const XMFLOAT3 INITDIR{ 0,0,1 };
	const XMFLOAT3 REF_POS[3]{ {-0.35f, 0.0f, 0.0f}, {0.0f,0.0f,0.0f}, {0.35f,0.0f,0.0f} };
	const float TRAVERSAL_TIME{ 600.0f };
	const float TRAVERSAL_ANGLE{ 85 };
	const float ROTANGLE[5]{ 0, -90, 180, 90, 0 };
	enum OPOS_STATE{ OLEFT, OCENTER, ORIGHT, MAXPOS};
	enum INPUT_STATE{ILEFT,IRIGHT, NONE, IMAX};
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

	OPOS_STATE posState_;
	OPOS_STATE posSetter(INPUT_STATE inputDir);

	bool isTraverasal() { return(ossanState_ == TRAVERSAL); }
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
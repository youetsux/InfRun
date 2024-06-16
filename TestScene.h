#pragma once
#include "Engine/GameObject.h"
#include "CDTimer.h"
#include "wanwanGenerator.h"
#include "UIImage.h"

namespace
{
	enum PLAYSTATE
	{
		READY, PLAY, DEAD, PMAX
	};
	const float GPERIODS[PMAX]{ 10.0, 1.0, 5.0 };
}


class Ossan;
class Ground;

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	int msgBoard_;
	Ossan* player;
	Ground* ground;
	XMFLOAT3 camPos_;
	CDTimer*timer_;
	wanwanGenerator* wang;
	PLAYSTATE PSTATE;
	UIImage* uiImage_;
public:
	void PlayUpdate();
	void ReadyUpdate();
	//void EffectDraw();

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
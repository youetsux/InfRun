#pragma once
#include "Engine/GameObject.h"
#include "CDTimer.h"
#include "wanwanGenerator.h"

class Ossan;
class AnimePlane;
//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
	AnimePlane* player;
	XMFLOAT3 camPos_;
	CDTimer*timer_;
	wanwanGenerator* wang;
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
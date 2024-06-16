#pragma once
#include "Engine/GameObject.h"
#include "Wanwan.h"
#include <vector>


using std::vector;

namespace {
	std::pair<int, int> GENPAIR[] = { {1,2},{0,2},{0,1} };
	const XMFLOAT3 WAN_POS[3]{ {-0.35f, 0.0f, 20.0f}, {0.0f,0.0f,20.0f}, {0.35f,0.0f,20.0f} };
	const float GENTIME{ 1.0 };
}

class wanwanGenerator :
    public GameObject
{
	bool isGenerated_;
	int spaceLane_;
	int oldLane_;
	int GenerateNum(int _n);
	//vector<Wanwan*> wanList;
	vector<Transform> wanList;
	Wanwan* wan_;
	float speed_;
public:
	void Generate();
	void SetSpeed(float _speed);
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	wanwanGenerator(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


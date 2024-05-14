#pragma once
#include "Engine/GameObject.h"
#include <vector>

const int ROAD_NUM{ 25 };
const float GSPEED{ 0.01f };



//�e�X�g�V�[�����Ǘ�����N���X
class Ground : public GameObject
{

	int hmodel_;
	std::vector<Transform> gt;
	float scrollSpeed_;
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ground(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	int GetModelNum() { return hmodel_; }
	void SetScroolSpeed(float _speed) { scrollSpeed_ = _speed; }
};
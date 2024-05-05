#include "Ground.h"
#include "Engine/Model.h"





Ground::Ground(GameObject* parent)
	:GameObject(parent,"Ground"), hmodel_(-1)
{
}

void Ground::Initialize()
{
	hmodel_ = Model::Load("Ground_fix.fbx");
	assert(hmodel_ >= 0);
	for (int i = 0; i < ROAD_NUM; i++) {
		Transform tmp;
		tmp.scale_ = { 1, 1, 1 };
		tmp.position_ = { 0, 0, (float)(i * 2)   };
		/*if (i % 2)
			tmp.position_.y -= 0.02;*/
		gt.push_back(tmp);
	}
	scrollSpeed_ = GSPEED;
	//transform_.scale_ = { 1,1,1 };
	//transform_.position_ = { 0, 0, 0 };

}

void Ground::Update()
{
	static float totalMove = 0;
	static int gtNum = 10;
	for (int i = 0; i < ROAD_NUM; i++) {
		gt[i].position_.z = gt[i].position_.z - scrollSpeed_;
	}
	totalMove = totalMove + scrollSpeed_;
	if (totalMove >= 2.0)
	{
		if (gtNum == 0) {
			if(scrollSpeed_< 2.0)
				scrollSpeed_ += 0.0025;
			gtNum = 10;
		}
		gt.erase(gt.begin());
		Transform tmp;
		tmp.scale_ = { 1, 1, 1 };
		float zp = gt.back().position_.z;
		tmp.position_ = { 0, 0, (float)(zp + 2.0)};
		gt.push_back(tmp);
		totalMove = 0;
		gtNum--;
	}
}

void Ground::Draw()
{
	for (int i = 0; i < ROAD_NUM; i++) {
		Model::SetTransform(hmodel_, gt[i]);
		Model::Draw(hmodel_);
	}
}

void Ground::Release() 
{
}

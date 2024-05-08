#include "wanwanGenerator.h"
#include <set>
#include "Engine/Model.h"
#include "Engine/Debug.h"

int wanwanGenerator::GenerateNum(int _n)
{
	
	float thd = (float)rand() / RAND_MAX;
	if (thd > 0.5)
		return GENPAIR[_n].first;
	else
		return GENPAIR[_n].second;
}

void wanwanGenerator::Generate()
{
	isGenerated_ = false;
}

void wanwanGenerator::SetSpeed(float _speed)
{
	speed_ = _speed;
}



wanwanGenerator::wanwanGenerator(GameObject* parent)
	:GameObject(parent, "WG"), isGenerated_(false), oldLane_(1), speed_(0),wan_(nullptr)
{
	spaceLane_ = rand() % 3;
}

void wanwanGenerator::Initialize()
{
	wan_ = new Wanwan(this->GetParent());
	wan_->Initialize();
}

void wanwanGenerator::Update()
{
	if (!isGenerated_) {
		oldLane_ = spaceLane_;
		spaceLane_ = GenerateNum(oldLane_);
		Transform wpos[2];
		wpos[0].position_ = WAN_POS[GENPAIR[spaceLane_].first];
		wpos[1].position_ = WAN_POS[GENPAIR[spaceLane_].second];
		wanList.push_back(wpos[0]);
		wanList.push_back(wpos[1]);

		isGenerated_ = true;
	}

	for (auto& theI : wanList)
	{
		XMVECTOR mv{ 0,0,-1 };
		XMVECTOR tmp = XMLoadFloat3(&(theI.position_));
		tmp = tmp + speed_ * mv;
		XMStoreFloat3(&(theI.position_), tmp);
	}
	auto itr = wanList.begin();
	while (itr != wanList.end())
	{
		if (itr->position_.z < 0)
		{
			itr = wanList.erase(itr);
		}
		else
		{
			itr++;
		}
	}

}

void wanwanGenerator::Draw()
{
	for (auto& theI : wanList)
	{
		wan_->SetPosition(theI.position_);
		wan_->Draw();
	}
}

void wanwanGenerator::Release()
{
}

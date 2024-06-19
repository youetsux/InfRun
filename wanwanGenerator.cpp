#include "wanwanGenerator.h"
#include <set>
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "EffekseerVXF.h"

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
	:GameObject(parent, "WG"), isGenerated_(false), oldLane_(1), speed_(0)
{
	spaceLane_ = rand() % 3;
}

void wanwanGenerator::Initialize()
{
	//wan_ = new Wanwan(this->GetParent());
	//wan_ = Instantiate<Wanwan>(this->GetParent());
	//wan_->Initialize();
	EFFEKSEERLIB::gEfk->AddEffect("BOM", "explode.efk");
}

void wanwanGenerator::Update()
{
	if (!isGenerated_) {
		Wanwan* w[2]{ nullptr, nullptr };
		for (int i = 0; i < 2; i++)
			w[i] = Instantiate<Wanwan>(this->GetParent());
		oldLane_ = spaceLane_;
		spaceLane_ = GenerateNum(oldLane_);
		
		w[0]->SetPosition(WAN_POS[GENPAIR[spaceLane_].first]);
		w[1]->SetPosition(WAN_POS[GENPAIR[spaceLane_].second]);
		
		wanList.push_back(w[0]);
		wanList.push_back(w[1]);

		isGenerated_ = true;
	}

	for (auto& theI : wanList)
	{
		XMVECTOR mv{ 0,0,-1 };
		XMFLOAT3 fl3tmp = theI->GetPosition();
		XMVECTOR tmp = XMLoadFloat3(&fl3tmp);
		tmp = tmp + speed_ * mv;
		
		XMStoreFloat3(&(fl3tmp), tmp);
		theI->SetPosition(fl3tmp);
		if (theI->BomFlag())
		{
			EFFEKSEERLIB::EFKTransform t;
			XMMATRIX sc = XMMatrixScaling(0.5, 0.5, 0.5);
			XMStoreFloat4x4(&(t.matrix), sc*theI->GetWorldMatrix());
			t.isLoop = false;
			t.maxFrame = 80;
			t.speed = 1.0;
			EFFEKSEERLIB::gEfk->Play("BOM", t);
		}
	}
	//Debug::Log((int)wanList.size(), true);
	auto itr = wanList.begin();
	while (itr != wanList.end())
	{
		if ((*itr)->GetPosition().z < 0)
		{
			(*itr)->KillMe();
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
	//for (auto& theI : wanList)
	//{
	//	wan_->SetPosition(theI.position_);
	//	wan_->Draw();
	//}
}

void wanwanGenerator::Release()
{
}

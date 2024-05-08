#include "wanwanGenerator.h"
#include <set>
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

wanwanGenerator::wanwanGenerator(GameObject* parent)
	:GameObject(parent, "WG"), isGenerated_(false), oldLane_(1)
{
	spaceLane_ = rand() % 3;
}

void wanwanGenerator::Initialize()
{
}

void wanwanGenerator::Update()
{
	if (!isGenerated_) {
		oldLane_ = spaceLane_;
		spaceLane_ = GenerateNum(oldLane_);
		Wanwan* enemy[2]{ nullptr,nullptr };
		//Instantiateするんじゃなく、トランスフォームのリストを作ったほうがいいね。
		enemy[0] = Instantiate<Wanwan>(this);
		enemy[1] = Instantiate<Wanwan>(this);
		enemy[0]->SetPosition(WAN_POS[GENPAIR[spaceLane_].first]);
		enemy[1]->SetPosition(WAN_POS[GENPAIR[spaceLane_].second]);
		wanList.push_back(enemy[0]);
		wanList.push_back(enemy[1]);

		//Debug::Log(spaceLane_, true);
		isGenerated_ = true;
	}
	for (auto theI : wanList)
	{
	}

}

void wanwanGenerator::Draw()
{
}

void wanwanGenerator::Release()
{
}

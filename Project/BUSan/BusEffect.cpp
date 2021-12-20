#include "pch.h"

BusEffect::BusEffect()
{
}

BusEffect::~BusEffect()
{
}

void BusEffect::Init(int districtID, float x, float y)
{
	Speed = 500;
	DistrictID = districtID;
	mAniTime = 0;
	PosX = x;
	PosY = y;
	mbStoped = false;
	mbChecked = false;
}

void BusEffect::Move(float dTime)
{
	mAniTime += dTime;
	PosX += Speed * dTime;
}

void BusEffect::PauseBus()
{
	Speed = 0;
	mAniTime = 0;
	mbStoped = true;
	mbChecked = true;
}

void BusEffect::StartBus()
{
	Speed = 500;
	mbStoped = false;
}
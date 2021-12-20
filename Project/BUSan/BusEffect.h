#pragma once
class BusEffect
{
public : 
	BusEffect();
	~BusEffect();

	void Init(int districtID, float x, float y);

public :
	int DistrictID;
	float PosX, PosY;
	float Speed;

private :
	float mAniTime;
	bool mbStoped;
	bool mbChecked;

public : 
	void Move(float dTime);

	void  PauseBus();
	void StartBus();
	float GetAniTime() { return mAniTime; }
	bool  GetStoped()  { return mbStoped; }
	bool  GetChecked() { return mbChecked; }
};


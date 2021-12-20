#pragma once
class SignalLight : public BTGameObject
{
public :
	int CurrentState;    // 0 red, 1 yellow, 2 green

	bool IsChecked;

	float PosX,PosY;
	float Width, Height;

public :
	void SetBoxSize(int sizeX,int sizeY);
	void MovePos(int x, int y, int regenPos);
	void SetRandomSignal();
	void OnClickSignal();
};


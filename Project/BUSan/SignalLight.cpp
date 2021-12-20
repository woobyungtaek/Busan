#include "pch.h"

void SignalLight::SetBoxSize(int sizeX, int sizeY)
{
	Width = sizeX;
	Height = sizeY;
}

void SignalLight::MovePos(int x, int y, int regenPos)
{
	PosX += x;
	PosY += y;

	if(PosX < (Width *-1))
	{
		PosX = regenPos;
		SetRandomSignal();
	}
	Initialize(PosX,PosY,Width,Height);
}

void SignalLight::SetRandomSignal()
{
	IsChecked = false;
	srand(GetTickCount64());
	CurrentState = rand() % 2;
}

void SignalLight::OnClickSignal()
{
	CurrentState -= 1;
	if (CurrentState < 0)
	{
		CurrentState = 2;
	}
}

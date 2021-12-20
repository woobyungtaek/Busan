#pragma once
class AroundNode
{
public :
	AroundNode() : StationID(-1) {}
	short			StationID;
	BusTime		BusTimeTable[60];
};


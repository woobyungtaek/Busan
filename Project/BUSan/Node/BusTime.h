#pragma once
class BusTime
{
public :
	BusTime() : DepartureTime(0), ElapseTime(0), ArrivalTime(0) {}
	short DepartureTime;
	short ElapseTime;
	short ArrivalTime;
};
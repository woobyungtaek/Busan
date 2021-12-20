#pragma once
class StationNode
{
public :
	StationNode() : Name(""), StationID(-1), DistrictID(-1), EventID(-1) {}

	char			Name[20];
	short			StationID;
	short			DistrictID;
	short			EventID;
	AroundNode		AroundList[20];
};


#pragma once
const short INF=1000;
class RoutingTableItem
{
private:
	short destinationID;
	short distance;
	short nextHop;
public:
	RoutingTableItem(void);
	RoutingTableItem(short dstID,short dis,short nHop);
	~RoutingTableItem(void);
	short GetDestinationID();
	short GetDistance();
	short GetNextHop();
	void SetDestinationID(short dstID);
	void SetDistance(short dis);
	void SetNextHop(short nHop);
};


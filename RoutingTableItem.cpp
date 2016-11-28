#include "RoutingTableItem.h"


RoutingTableItem::RoutingTableItem(void)
{
	destinationID=nextHop=-1;
	distance=INF;
}


RoutingTableItem::~RoutingTableItem(void)
{
}


RoutingTableItem::RoutingTableItem(short dstID,short dis,short nHop)
{
	destinationID=dstID;
	distance=dis;
	nextHop=nHop;
}

short RoutingTableItem::GetDestinationID()
{
	return this->destinationID;
}

short RoutingTableItem::GetDistance()
{
	return this->distance;
}

short RoutingTableItem::GetNextHop()
{
	return this->nextHop;
}

void RoutingTableItem::SetDestinationID(short dstID)
{
	this->destinationID=dstID;
}

void RoutingTableItem::SetDistance(short dis)
{
	this->distance = dis > INF ? INF : dis;
}

void RoutingTableItem::SetNextHop(short nHop)
{
	this->nextHop=nHop;
}
#pragma once
#include "RoutingTableItem.h"
#include <vector>
#include <iostream>
using namespace std;
const short A='A',B='B',C='C',D='D',E='E';
class Router
{
private:
	vector<RoutingTableItem> RoutingTable;

	short id;
public:
	vector<short> adjacentRouter;
public:
	Router(short id);
	~Router(void);
	vector<RoutingTableItem> GetRoutingTable();
	short GetID();
	RoutingTableItem &GetVectorByDst(short id);
	bool FindVectorByDst(short id);
	void AddItem(RoutingTableItem &item);
	void AddAdjacentRouter(short id);
	bool UpdateFrom(Router incomingRouter);
	void output();
	
};


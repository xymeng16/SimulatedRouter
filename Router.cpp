#include "Router.h"
#include <algorithm>
int lastUpdatingTimes,currentUpdatingTimes;
extern bool isConvergent;
Router::Router(short id)
{
	this->id=id;
}


Router::~Router(void)
{
}


vector<RoutingTableItem> Router::GetRoutingTable()
{
	return this->RoutingTable;
}


short Router::GetID()
{
	return this->id;
}


RoutingTableItem &Router::GetVectorByDst(short id)
{
	for(int i=0;i<this->RoutingTable.size();i++)
	{
		if(id==this->RoutingTable[i].GetDestinationID())
			return this->RoutingTable[i];
	}
	return *(new RoutingTableItem());
}


bool Router::FindVectorByDst(short id)
{
	for(int i=0;i<this->RoutingTable.size();i++)
	{
		if(id==this->RoutingTable[i].GetDestinationID())
			return true;
	}
	return false;
}

void Router::AddItem(RoutingTableItem &item)
{
	this->RoutingTable.push_back(item);
}

void Router::AddAdjacentRouter(short id)
{
	adjacentRouter.push_back(id);
}


bool Router::UpdateFrom(Router incomingRouter)
{
	lastUpdatingTimes=currentUpdatingTimes;
	vector<RoutingTableItem> incomingTable=incomingRouter.GetRoutingTable();
	size_t size=incomingTable.size();
	RoutingTableItem toLocalItem=incomingRouter.GetVectorByDst(this->GetID());
	for(int i=0;i<size;i++)
	{
		incomingTable[i].SetNextHop(incomingRouter.GetID());
		incomingTable[i].SetDistance(incomingTable[i].GetDistance()+toLocalItem.GetDistance());

	}
	// For each item in the incoming table, proceed thses processes below
	// If destination network N doesn't exist in local table, add it.
	// else
	// ,observing that now the current local item has the same destination network with current incoming item, 
	// if current local item's nextHop is equal to incoming Router ID 'X', then replace the current
	// item with incoming item, that is to say, we update the distance.
	// else (now the current local item has destination network N, but its nextHop isn't X)
	// if the distance in the incoming item is less than the current local item, update it, else do nothing.
	for(int i=0;i<size;i++)
	{
		RoutingTableItem &cur=this->GetVectorByDst(incomingTable[i].GetDestinationID());
		if(incomingTable[i].GetDistance()==INF&&incomingTable[i].GetNextHop()==incomingTable[i].GetDestinationID())
		{
			vector<short>::iterator result=find(adjacentRouter.begin(),adjacentRouter.end(),incomingTable[i].GetNextHop());
			if(result!=adjacentRouter.end())
				adjacentRouter.erase(result);
			continue;
		}
		if(cur.GetDestinationID()==INF)
		{
			// Add new item
			this->AddItem(incomingTable[i]);
			currentUpdatingTimes++;
		}
		else
		{
			if(cur.GetNextHop()==incomingRouter.GetID())
			{
				// Update
				if (cur.GetDistance() != incomingTable[i].GetDistance())
				{
					cur.SetDistance(incomingTable[i].GetDistance());
					currentUpdatingTimes++;
				}
			}
			else
			{
				// Compare the value and decide whether to update or not
				if(cur.GetDistance()>incomingTable[i].GetDistance())
				{
					cur.SetDistance(incomingTable[i].GetDistance());
					cur.SetNextHop(incomingTable[i].GetNextHop());
					currentUpdatingTimes++;
				}
			}
		}
	}
	return true;
}

void Router::output()
{
	printf("Destination\tDistance\tNextHop\n");
	for(int i=0;i<this->RoutingTable.size();i++)
	{
		printf("    %c    \t    %d    \t   %c   \n",this->RoutingTable[i].GetDestinationID(),this->RoutingTable[i].GetDistance(),this->RoutingTable[i].GetNextHop());
	}
}

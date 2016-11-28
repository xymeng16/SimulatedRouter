#include <iostream>
#include "RoutingTableItem.h"
#include "Router.h"
#include <vector>
#include <algorithm>

using namespace std;
extern int lastUpdatingTimes,currentUpdatingTimes;
Router RouterA(A),RouterB(B),RouterC(C),RouterD(D),RouterE(E);
Router *Routers[5] = { &RouterA,&RouterB,&RouterC,&RouterD,&RouterE };
bool isConvergent=false;
void RoutingTableInit()
{
	RouterA.AddItem(*(new RoutingTableItem(A,0,A)));
	RouterA.AddItem(*(new RoutingTableItem(B,7,B)));
	RouterA.AddItem(*(new RoutingTableItem(C,INF,C)));
	RouterA.AddItem(*(new RoutingTableItem(D,INF,D)));
	RouterA.AddItem(*(new RoutingTableItem(E,1,E)));
	RouterA.AddAdjacentRouter(B);
	RouterA.AddAdjacentRouter(E);

	RouterB.AddItem(*(new RoutingTableItem(A,7,A)));
	RouterB.AddItem(*(new RoutingTableItem(B,0,B)));
	RouterB.AddItem(*(new RoutingTableItem(C,1,C)));
	RouterB.AddItem(*(new RoutingTableItem(D,INF,D)));
	RouterB.AddItem(*(new RoutingTableItem(E,8,E)));
	RouterB.AddAdjacentRouter(A);
	RouterB.AddAdjacentRouter(C);
	RouterB.AddAdjacentRouter(E);

	RouterC.AddItem(*(new RoutingTableItem(A,INF,A)));
	RouterC.AddItem(*(new RoutingTableItem(B,1,B)));
	RouterC.AddItem(*(new RoutingTableItem(C,0,C)));
	RouterC.AddItem(*(new RoutingTableItem(D,2,D)));
	RouterC.AddItem(*(new RoutingTableItem(E,INF,E)));
	RouterC.AddAdjacentRouter(B);
	RouterC.AddAdjacentRouter(D);

	RouterD.AddItem(*(new RoutingTableItem(A,INF,A)));
	RouterD.AddItem(*(new RoutingTableItem(B,INF,B)));
	RouterD.AddItem(*(new RoutingTableItem(C,2,C)));
	RouterD.AddItem(*(new RoutingTableItem(D,0,D)));
	RouterD.AddItem(*(new RoutingTableItem(E,2,E)));
	RouterD.AddAdjacentRouter(C);
	RouterD.AddAdjacentRouter(E);

	RouterE.AddItem(*(new RoutingTableItem(A,1,A)));
	RouterE.AddItem(*(new RoutingTableItem(B,8,B)));
	RouterE.AddItem(*(new RoutingTableItem(C,INF,C)));
	RouterE.AddItem(*(new RoutingTableItem(D,2,D)));
	RouterE.AddItem(*(new RoutingTableItem(E,0,E)));
	RouterE.AddAdjacentRouter(A);
	RouterE.AddAdjacentRouter(B);
	RouterE.AddAdjacentRouter(D);

}

void outputAll()
{
	RouterA.output();
	RouterB.output();
	RouterC.output();
	RouterD.output();
	RouterE.output();
}
void Update()
{
	cout << "Updating......" << endl;
	do
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < Routers[i]->adjacentRouter.size(); j++)
			{
				Routers[i]->UpdateFrom(*Routers[(Routers[i]->adjacentRouter[j]) - 'A']);
			}
		}
		//cout << "Looping......\r" << endl;
		outputAll();
		//system("read");
		getchar();
	} while (lastUpdatingTimes != currentUpdatingTimes);
	isConvergent=true;
}

int main()
{
	RoutingTableInit();
	/*RouterA.output();
	RouterB.output();
	RouterC.output();
	RouterD.output();
	RouterE.output();*/
	Update();
	//isConvergent=true;
	cout << "Done!" << endl;
	cout << "Now break the connection between B and C. Redo the process." << endl;
	// How to let other virtual routers know that the connection between B and C was broken?
	//getchar();
	RouterB.GetVectorByDst(C).SetDistance(INF);
	//RouterB.GetVectorByDst(C).SetDestinationID(C);
	RouterC.GetVectorByDst(B).SetDistance(INF);
	//RouterC.GetVectorByDst(B).SetDestinationID(B);
	outputAll();
	getchar();
	Update();
	cout << "Done" << endl;
	outputAll();
	return 0;
}

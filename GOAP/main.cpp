#include <cstdlib>
#include "NPC.h"

#include "GoapAgent.h"

int main()
{
	NPC* npc = new NPC();

	while (true)
	{
		npc->Update();
	}

	system("pause");
	return 0;
}
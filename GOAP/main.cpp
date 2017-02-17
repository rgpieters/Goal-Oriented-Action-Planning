#include <cstdlib>
#include "NPC.h"

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
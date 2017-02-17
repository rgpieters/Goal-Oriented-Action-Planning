#ifndef _NPC_H_
#define _NPC_H_

#include "BaseObject.h"

class NPC : BaseObject
{
public:
	NPC();
	NPC(const NPC&);
	~NPC();

	void Update();

private:
	std::unordered_map<std::string, bool> CreateGoalState();
};

#endif
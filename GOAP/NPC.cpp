#include "NPC.h"

NPC::NPC()
{

}

NPC::NPC(const NPC&)
{

}

NPC::~NPC()
{

}

void NPC::Update()
{
	BaseObject::Update();
	int x = 10;
}

std::unordered_map<std::string, bool> NPC::CreateGoalState()
{
	std::unordered_map<std::string, bool> goal;
	goal.insert(goal.end(), std::pair<std::string, bool>("hasAJob", true));

	return goal;
}
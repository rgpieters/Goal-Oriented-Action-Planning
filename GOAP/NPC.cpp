#include "NPC.h"
#include "WriteApplicationAction.h"
#include "GoapAgent.h"

#include "GoapState.h"

NPC::NPC()
{
	m_WriteAction = new WriteApplicationAction();
	AddAction((GoapAction*)m_WriteAction);
	m_GoapAgent = new GoapAgent(this);
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
}

std::unordered_map<std::string, bool> NPC::CreateGoalState()
{
	std::unordered_map<std::string, bool> goal;
	goal.insert(goal.end(), std::pair<std::string, bool>("applicationWritten", true));

	return goal;
}
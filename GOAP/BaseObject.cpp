#include "BaseObject.h"
#include "GoapAgent.h"

BaseObject::BaseObject()
{
	// NOTE: This will need to be done the child class after actions have been initialized
	//m_GoapAgent = new GoapAgent(this);
}

BaseObject::BaseObject(const BaseObject&)
{

}

BaseObject::~BaseObject()
{
	if (m_GoapAgent)
	{
		delete m_GoapAgent;
		m_GoapAgent = nullptr;
	}
}

std::unordered_map<std::string, bool> BaseObject::GetWorldState()
{
	std::unordered_map<std::string, bool> worldData;
	worldData.insert(worldData.begin(), std::pair<std::string, bool>("applicationWritten", false));

	return worldData;
}

void BaseObject::Update()
{
	m_GoapAgent->Update(this);
}

void BaseObject::PlanFailed(std::unordered_map<std::string, bool> failedGoal)
{
	// something checking to the world state has changed before running same goal agin
}

void BaseObject::PlanFound(std::unordered_map<std::string, bool> goal, std::queue<GoapAction*> actions)
{
	// message found plan
}

void BaseObject::ActionsFinished()
{
	// message actions finished
}

void BaseObject::PlanAborted(GoapAction* aborter)
{
	// message plan aborted
}

bool BaseObject::MoveAgent(GoapAction* nextAction)
{
	// movement of object
	return true;
}
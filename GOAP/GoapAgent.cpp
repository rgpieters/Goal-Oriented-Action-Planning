#include "GoapAgent.h"
#include "IGoap.h"
#include "GoapAction.h"
#include "BaseObject.h"
#include "GoapPlanner.h"

GoapAgent::GoapAgent()
{

}

GoapAgent::GoapAgent(BaseObject* object)
{
	m_GoapPlanner = new GoapPlanner();
	FindDataProvider(object);
	m_IdleState = new GoapState(&GoapAgent::IdleStateUpdate, this);
	m_MoveState = new GoapState(&GoapAgent::MoveStateUpdate, this);
	m_PerformActionState = new GoapState(&GoapAgent::PerformActionStateUpdate, this);
	m_StateStack.push(m_IdleState);
	LoadActions(object);
}

GoapAgent::GoapAgent(const GoapAgent&)
{

}

GoapAgent::~GoapAgent()
{
	if (m_GoapPlanner)
	{
		delete m_GoapPlanner;
		m_GoapPlanner = nullptr;
	}

	if (m_IdleState)
	{
		delete m_IdleState;
		m_IdleState = nullptr;
	}

	if (m_MoveState)
	{
		delete m_MoveState;
		m_MoveState = nullptr;
	}

	if (m_PerformActionState)
	{
		delete m_PerformActionState;
		m_PerformActionState = nullptr;
	}
}

void GoapAgent::AddAction(GoapAction* action)
{
	m_PossibleActions.insert(action);
}

void GoapAgent::RemoveAction(GoapAction* action)
{
	m_PossibleActions.erase(action);
}

int GoapAgent::IdleStateUpdate(BaseObject* object)
{
	std::unordered_map<std::string, bool> worldState = m_DataProvider->GetWorldState();
	std::unordered_map<std::string, bool> goal = m_DataProvider->CreateGoalState();

	std::queue<GoapAction*> plan = m_GoapPlanner->Plan(object, m_PossibleActions, worldState, goal);
	if (!plan.empty())
	{
		m_CurrentActions = plan;
		m_DataProvider->PlanFound(goal, plan);

		m_StateStack.pop();
		m_StateStack.push(m_PerformActionState);

		return 1;
	}
	else
	{
		m_StateStack.pop();
		m_StateStack.push(m_IdleState);

		return 1;
	}
}

int GoapAgent::MoveStateUpdate(BaseObject* object)
{
	GoapAction* action = m_CurrentActions.front();
	if (action->RequiresInRange() && action->Target() == nullptr)
	{
		m_StateStack.pop();
		m_StateStack.pop();
		m_StateStack.push(m_IdleState);
		return 1;
	}

	if (m_DataProvider->MoveAgent(action))
	{
		m_StateStack.pop();
	}

	return 1;
}

int GoapAgent::PerformActionStateUpdate(BaseObject* object)
{
	if (!HasActionPlan())
	{
		m_StateStack.pop();
		m_StateStack.push(m_IdleState);
		m_DataProvider->ActionsFinished();
		return 1;
	}

	GoapAction* action = m_CurrentActions.front();
	if (action->IsDone())
	{
		m_CurrentActions.pop();
	}

	if (HasActionPlan())
	{
		action = m_CurrentActions.front();

		bool inRange = action->RequiresInRange() ? action->IsInRange() : true;
		if (inRange)
		{
			bool success = action->PerformAction(object);

			if (!success)
			{
				m_StateStack.pop();
				m_StateStack.push(m_IdleState);
				m_DataProvider->PlanAborted(action);
			}
			else
			{
				m_StateStack.push(m_MoveState);
			}
		}
		else
		{
			m_StateStack.pop();
			m_StateStack.push(m_IdleState);
			m_DataProvider->ActionsFinished();
		}
	}

	return 1;
}

void GoapAgent::Update(BaseObject* object)
{
	m_StateStack.top()->Update(object);
}

bool GoapAgent::HasActionPlan()
{
	return m_CurrentActions.size() > 0;
}

void GoapAgent::FindDataProvider(BaseObject* object)
{
	m_DataProvider = (IGoap*)object;
}

void GoapAgent::LoadActions(BaseObject* object)
{
	for (auto i = 0u; i < object->GetActions().size(); i++)
	{
		m_PossibleActions.insert(m_PossibleActions.end(), object->GetActions()[i]);
	}
}
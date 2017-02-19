#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

#include "GoapState.h"

#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <string>

class IGoap;
class GoapAction;
class GoapPlanner;
class BaseObject;

class GoapAgent
{
public:
	GoapAgent();
	GoapAgent(BaseObject* object);
	GoapAgent(const GoapAgent&);
	~GoapAgent();

	void Update(BaseObject* object);
	void AddAction(GoapAction* action);
	void RemoveAction(GoapAction* action);

private:
	std::stack<GoapState*> m_StateStack;

	GoapState* m_IdleState;
	GoapState* m_MoveState;
	GoapState* m_PerformActionState;

	std::set<GoapAction*> m_PossibleActions;
	std::queue<GoapAction*> m_CurrentActions;

	IGoap* m_DataProvider;

	GoapPlanner* m_GoapPlanner;

	int IdleStateUpdate(BaseObject* object);
	int MoveStateUpdate(BaseObject* object);
	int PerformActionStateUpdate(BaseObject* object);

	bool HasActionPlan();
	void FindDataProvider(BaseObject* object);
	void LoadActions(BaseObject* object);
};

#endif
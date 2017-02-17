#ifndef _GOAP_AGENT_H_
#define _GOAP_AGENT_H_

#include <stack>
#include <queue>
#include <set>
#include <unordered_map>
#include <string>

class GoapState;
class IGoap;
class GoapAction;
class GoapPlanner;
class BaseObject;

class GoapAgent
{
private:
	std::stack<GoapState*> m_StateStack;

	GoapState* m_IdleState;
	GoapState* m_MoveState;
	GoapState* m_PerformActionState;

	std::set<GoapAction*> m_PossibleActions;
	std::queue<GoapAction*> m_CurrentActions;

	IGoap* m_DataProvider;

	GoapPlanner* m_GoapPlanner;

	void IdleStateUpdate(BaseObject* object);
	void MoveStateUpdate(BaseObject* object);
	void PerformActionStateUpdate(BaseObject* object);

	bool HasActionPlan();
	void FindDataProvider(BaseObject* object);
	void LoadActions(BaseObject* object);

public:
	GoapAgent(BaseObject* object);
	GoapAgent(const GoapAgent&);
	~GoapAgent();

	void Update(BaseObject* object);
	void AddAction(GoapAction* action);
	void RemoveAction(GoapAction* action);
};

#endif